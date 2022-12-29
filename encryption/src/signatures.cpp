#include "signatures.h"
#include "number.h"

SigType Signature::GetType() const
{
    string name = typeid(*this).name();

    if (name == "12DSASignature")
        return DSA;
    else if (name == "16SchnorrSignature")
        return Schnorr;
    else
        throw invalid_argument("Signature Type does not exist!");
}

//Todo: Constructors/Destructors
Signature::Signature() {}
Signature::~Signature() {}
SchnorrSignature::SchnorrSignature(const Number * s, const Number * e) : s{s}, e{e} {}
SchnorrSignature::~SchnorrSignature() { 
    delete s; delete e; 
    cout << "Destruct SchnorrSignature..." << endl;
}
DSASignature::DSASignature(const Number * r, const Number * s) : r{r}, s{s} {}
DSASignature::~DSASignature() { 
    delete r; delete s; 
    cout << "Destruct DSASignature..." << endl;
}
PublicKey::PublicKey() {}
PublicKey::~PublicKey() {}
SchnorrPublicKey::~SchnorrPublicKey() { 
    delete y; 
    cout << "Destruct SchnorrPublicKey..." << endl;
}
DSAPublicKey::DSAPublicKey(const Number * y) : y{y} {}
DSAPublicKey::~DSAPublicKey() { 
    delete y; 
    cout << "Destruct DSAPublicKey..." << endl;
}
SecretKey::SecretKey() {}
SecretKey::~SecretKey() {}
SchnorrSecretKey::SchnorrSecretKey(const Number * x) : x{x} {}
SchnorrSecretKey::~SchnorrSecretKey() { 
    delete x; 
    cout << "Destruct SchnorrSecretKey..." << endl;
}
DSASecretKey::~DSASecretKey() { 
    delete x; 
    cout << "Destruct DSASecretKey..." << endl;
}


bool SchnorrPublicKey::Verify(const string &message, const Signature &signature) const
{
    //Todo

    const SchnorrSignature& sig = dynamic_cast<const SchnorrSignature&>(signature);

    // step 1
    // check upper bound for s
    Number t1 = Number::Sub(*Number::Q, *(sig.s));
    if (Number::NSign(t1) < 1) {
        return false;
    }
    // check upper bound for e
    Number t2 = Number::Sub(*Number::Q, *(sig.e));
    if (Number::NSign(t2) < 1) {
        return false;
    }
    // check lower bound for s and e
    if (Number::NSign(*(sig.s)) < 1 || Number::NSign(*(sig.e)) < 1 ) {
        return false;
    }

    // step 2
    Number rv = Number::Mul_Mod(Number::Pow(*Number::G, *sig.s, *Number::P), Number::Pow(*y, *sig.e, *Number::P), *Number::P);
    // step 3
    Number ev = Number::Mod(Number::Hash(rv, message), *Number::Q);
    // step 4
    if (Number::NSign(Number::Sub(ev, *sig.e)) == 0) {
        return true;
    }
    
    return false;
}


bool DSAPublicKey::Verify(const string &message, const Signature &signature) const
{
    //Todo

    const DSASignature& sig = dynamic_cast<const DSASignature&>(signature);
    // step 1
    // check upper bound for r
    Number t1 = Number::Sub(*Number::Q, *(sig.r));
    if (Number::NSign(t1) < 1) {
        return false;
    }
    // check upper bound for s
    Number t2 = Number::Sub(*Number::Q, *(sig.s));
    if (Number::NSign(t2) < 1) {
        return false;
    }
    // check lower bound for r and s
    if (Number::NSign(*(sig.r)) < 1 || Number::NSign(*(sig.s)) < 1 ) {
        return false;
    }

    // step 2
    Number w = Number::Mod(Number::Inv(*sig.s, *Number::Q), *Number::Q);
    // step 3
    Number z = Number::Hash(message);
    // step 4
    Number u1 = Number::Mul_Mod(Number::Mod(z, *Number::Q), Number::Mod(w, *Number::Q), *Number::Q);
    // step 5
    Number u2 = Number::Mul_Mod(Number::Mod(*sig.r, *Number::Q), Number::Mod(w, *Number::Q), *Number::Q);
    // step 6
    if (Number::NSign(Number::Sub(Number::Mod(Number::Mul_Mod(Number::Pow(*Number::G, u1, *Number::P), Number::Pow(*y, u2, *Number::P), *Number::P), *Number::Q), *sig.r)) == 0) {
        return true;
    }
    
    return false;
}



const Signature *SchnorrSecretKey::Sign(const string &message) const
{
    //Todo
    while (true) {
        // step 1
        Number k = Number::Rand(1, *Number::Q);
        // step 2
        Number r = Number::Pow(*Number::G, k, *Number::P);
        // step 3
        Number e = Number::Mod(Number::Hash(r, message), *Number::Q);
        // step 4
        Number s = Number::Mod(Number::Sub(k, Number::Mul_Mod(*x, e, *Number::Q)), *Number::Q);
        // step 5
        if (Number::NSign(s) > 0 && Number::NSign(e) > 0) {
            return new SchnorrSignature(new Number(s), new Number(e));
        }
    }
}



const Signature *DSASecretKey::Sign(const string &message) const
{
    while (true)
    {
        Number k = Number::Rand(1, *Number::Q);
        Number r = Number::Mod(Number::Pow(*Number::G, k, *Number::P), *Number::Q);
        Number z = Number::Hash(message);
        Number zxr = Number::Mod(Number::Add(z, Number::Mul_Mod(*(this->x), r, *Number::Q)), *Number::Q);
        Number ki = Number::Inv(k, *Number::Q);
        Number s = Number::Mul_Mod(ki, zxr, *Number::Q);

        if (Number::NSign(r) > 0 && Number::NSign(s) > 0)
            return new DSASignature(new Number(r), new Number(s));
    }
}

SigPair::SigPair(const PublicKey *publicKey, const SecretKey *secretKey)
    : publicKey(publicKey), secretKey(secretKey)
{
}

SigPair::~SigPair()
{
    cout << "Destruct SigPair..."<<endl;
    delete publicKey;
    delete secretKey;
}

const SigPair *GenerateKey(SigType sigType, const string &info)
{
    if (sigType == DSA )
    {
        Number x = Number::Rand(Number(1), *Number::Q);
        Number y = Number::Pow(*Number::G, x, *Number::P);
        const Number *newX = new Number(x);
        const Number *newY = new Number(y);

        DSASecretKey *sk = new DSASecretKey(newX);
        DSAPublicKey *pk = new DSAPublicKey(newY);

        SigPair *sigPair = new SigPair(pk, sk);

        return sigPair;
    }
    else if (sigType == Schnorr )
    {
        //Todo
        Number x = Number::Rand(Number(1), *Number::Q);
        Number y = Number::Pow(*Number::G, x, *Number::P);
        const Number *newX = new Number(x);
        const Number *newY = new Number(y);
        SchnorrSecretKey *sk = new SchnorrSecretKey(newX);
        SchnorrPublicKey *pk = new SchnorrPublicKey(newY);
        SigPair *sigPair = new SigPair(pk, sk);


        return sigPair;
    }
    return nullptr;
}

vector<SigType> SigTypes()
{
    vector<SigType> s;
    s.push_back(DSA);
    s.push_back(Schnorr);
    return s;
}

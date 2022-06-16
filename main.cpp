#include <iostream>
#include <cmath>
#include <vector>
using namespace std;
class Polynomial{
protected:
    class Term{
    public:
        int exponent; int coefficient; Term *next;
        Term(){};
        Term(int exp, int coeff, Term *n): exponent(exp), coefficient(coeff), next(n){}
        friend class Polynomial;
    };
public:
    Polynomial(): head(nullptr), size(0){};
    Polynomial(const Polynomial &p): size(p.size){
        if(p.head == nullptr){head = nullptr;}
        else {
            Term *q = nullptr;
            Term *f = p.head;
            bool first = true;
            while (f != nullptr) {
                if(first){
                    head = new Term(f->exponent, f->coefficient, nullptr);
                    first = false;
                    q = head;
                    f = f->next;
                }else{
                    Term *nod = new Term(f->exponent, f->coefficient, nullptr);
                    q->next = nod;
                    q = nod;
                    f=f->next;
                }
            }
        }

    };
    ~Polynomial(){
        Term *f = head;
        while(f!= nullptr){
            Term *r = f;
            f = f->next;
            delete r;

        }
    }

    Polynomial & operator = (const Polynomial &p){
        Term *f = head;
        while(f!= nullptr){
            Term *r = f;
            f = f->next;
            delete r;

        }
        size = p.size;
        if(p.head == nullptr){head = nullptr;}
        else {
            Term *q = nullptr;
            Term *f = p.head;
            bool first = true;
            while (f != nullptr) {
                if(first){
                    head = new Term(f->exponent, f->coefficient, nullptr);
                    first = false;
                    q = head;
                    f = f->next;
                }else{
                    Term *nod = new Term(f->exponent, f->coefficient, nullptr);
                    q->next = nod;
                    q = nod;
                    f=f->next;
                }
            }
        }
        return *this;
    }

    void addTerm(int expon, int coeff){
        if(size == 0){
            head = new Term(expon, coeff, nullptr);
            size++;
        }else {
            if (coeff != 0) {
                Term *q;
                Term *p = head;

                while (p->next != nullptr && p->next->exponent >= expon) {
                    q = p;
                    p = p->next;
                }
                if (p->exponent == expon) {
                    p->coefficient += coeff;
                    if(p->coefficient == 0){
                        size--;
                        if(p == head){
                            head = p->next;
                            delete p;
                        }else{
                            q->next = p->next;
                            delete p;
                        }

                    }
                } else {
                    if (p == head && head->exponent < expon) {
                        Term *q = new Term(expon, coeff, head);
                        head = q;
                        size++;

                    } else {
                        Term *q = new Term(expon, coeff, p->next);
                        p->next = q;
                        size++;

                    }
                }
            }
        }
    }
    double evaluate(double x){
        ans = 0;
        Term *p = head;
        while(p!= nullptr){
            ans+=pow(x, p->exponent)*(p->coefficient);
            p = p->next;
        }
        return ans;
    };

    friend Polynomial operator+(const Polynomial &p, const Polynomial &q){
        int x= 0;
        int y = 0;
        if(p.head!=nullptr){
            x = p.head->exponent;}
        if(q.head!=nullptr) {
            y = q.head->exponent;
        }
        vector<int> v;
        int s = max(x,y);
        v.resize(max(x,y)+1);
        Term *l = p.head;
        while(l!= nullptr){
            v[l->exponent]+=l->coefficient;
            l = l->next;
        }
        Term *f = q.head;
        while(f!=nullptr){
            v[f->exponent]+=f->coefficient;
            f = f->next;
        }
        Polynomial pol;
        for(int i = s; i >= 0; i--){
            if(v[i]!=0){
                pol.addTerm(i,v[i]);
            }
        }
        return pol;




    }
    friend Polynomial operator*(const Polynomial &p, const Polynomial &q){
        if(p.head == nullptr || q.head == nullptr){
            Polynomial f;
            return f;
        }
        int x= 0;
        int y = 0;
        x = p.head->exponent;
        y = q.head->exponent;

        vector<int> v;
        int s = x+y;
        v.resize(s+1);
        Term *one = p.head;
        while(one!=nullptr){
            Term *two = q.head;
            while(two!=nullptr){
                v[one->exponent+two->exponent]+=(one->coefficient*two->coefficient);
                two = two->next;
            }
            one = one->next;
        }


        Polynomial pol;
        for(int i = s; i >= 0; i--){
            if(v[i]!=0){
                pol.addTerm(i,v[i]);
            }
        }
        return pol;


    }

    friend ostream & operator << (ostream &out, const Polynomial &p) {
        if(p.head == nullptr){
            out << 0; //maybe not
        }else{
            Term *s = p.head;
            bool first = true;
            while(s!=nullptr){
                if(s->coefficient!=0) {
                    if (first) {
                        if (s->coefficient < 0) {
                            out << "- ";
                        }
                        if (s->coefficient != 1 && s->coefficient != -1) {
                            out << abs(s->coefficient);
                        }
                        if (s->exponent == 0) {
                            if (s->coefficient == 1 || s->coefficient == -1) { out << abs(s->coefficient); }
                        } else if (s->exponent == 1) {
                            out << "x";
                        } else {
                            out << "x^" << s->exponent;
                        }
                        first = false;
                    } else {
                        if (s->coefficient < 0) {
                            out << " - ";
                        } else {
                            out << " + ";
                        }
                        if (s->coefficient != 1 && s->coefficient != -1) {
                            out << abs(s->coefficient);
                        }
                        if (s->exponent == 0) {
                            if (s->coefficient == 1 || s->coefficient == -1) { out << abs(s->coefficient); }
                        } else if (s->exponent == 1) {
                            out << "x";
                        } else {
                            out << "x^" << s->exponent;
                        }

                    }
                }
                s=s->next;

            }
        }
        return out;
    }

private:
    Term *head;
    int size;
    double ans;
};

int main() {
    Polynomial p;
    p.addTerm(1,-3);
    p.addTerm(2,1);
    p.addTerm(0,10);
    Polynomial f = p+p;
    cout << p.evaluate(1);
    Polynomial r =p*p;
    cout << r.evaluate(0);
    cout << r.evaluate(1) << "\n";
    r = p;
    cout << p << "\n";

    return 0;
}
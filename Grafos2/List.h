#ifndef _H_Lista_
#define _H_Lista_
using namespace std;

template <class T>
class Node
{
    T info;
    Node<T> *next, *prev;
    
public:
    Node(): next(NULL), prev(NULL){}
    ~Node()
    {
        prev->next = NULL;
        delete next;
    }
    
    Node(T nInfo){ setInfo(nInfo); };
    
    void setInfo(T nInfo){ info = nInfo; }
    
    void setNext(Node<T>* nNext){ next = nNext;}
    
    void setPrev(Node<T>* nPrev){ prev = nPrev; }
    
    T& getInfo() { return info; }
    
    Node<T>* getNext(){ return next; }
    
    Node<T>* getPrev(){ return prev; }
    
    void bind(Node<T>* toBind)
    {
        this->setNext(toBind);
        toBind->setPrev(this);
    }
};

template <class T>
class List
{
    uint longitud;
    Node<T> *header,*itt;
    uint ittpos;
    
public:
    List() : longitud(0), header(NULL), itt(NULL), ittpos(0){};
    ~List()
    {
        this->deleteAll();
    }
    
    int lenght()  { return longitud; }
    
    bool isEmpty(){ return lenght() == 0;}
    
    void setInfoAtPos(T nInfo,int pos)
    {
        if (pos<0 || pos>=lenght()) return;
        goTo(pos)->setInfo(nInfo);
    }

    void addInfoAtPos(T nInfo,int pos)
    {
        Node<T>* nodeAux, *nNode;
        
        if (pos < 0 || pos>lenght()) return;
        
        nNode = new Node<T>(nInfo);
        
        if (pos==0){
            nNode->bind(nNode);
            if (header!=NULL) {
                nNode->setPrev(header->getPrev());
                nNode->setNext(header->getNext());
                
                header->getPrev()->bind(nNode);
                nNode->bind(header);
            }
            header = nNode;
        }
        else if (pos==lenght())
        {
            nodeAux = header->getPrev();
            nodeAux->bind(nNode);
            nNode->bind(header);
            
        }
        else{
            nodeAux = goTo(pos);
            nodeAux->getPrev()->bind(nNode);
            nNode->bind(nodeAux);
        }
        longitud++;
    }

    void deleteAtPos(int pos){
        Node<T>* nodeAux;
                    
        if (pos < 0 || pos>=lenght()) return;
        
        if (pos == 0)
        {
            nodeAux = header;
            header = nodeAux->getNext();
            header->setPrev(nodeAux->getPrev());//circular
        }
        else {
            nodeAux = goTo(pos);
            nodeAux->getPrev()->bind(nodeAux->getNext());
        }
        longitud--;
        delete(nodeAux);
    }

    int getPosWithInfo(T info){
        Node<T> *nodeAux = header;
        int pos=-1;
        for (int i=0; i<=lenght();i++){
            if (nodeAux->getInfo() == info)
                pos = i;
            nodeAux = nodeAux->getNext();
        }
        return pos;
    }

    T& getInfoWithPos(int pos){
        if (pos < 0 || pos>=lenght()) return *(new T);
        return goTo(pos)->getInfo();
        
    }

    void deleteAll()
    {
        delete header;
        header = NULL;
        
    }


    void imprimirLog()
    {
        if (isEmpty())
            cout << "lista está vacia" <<endl;
        for (int i=0; i<lenght();i++)
            cout << i<< ". " << goTo(i)->getInfo() <<endl;
        cout<<endl;
    }

    List<T>& operator=(List<T>& asignador)
    {
        Node<T>* auxA = asignador.header;
        if (&asignador != this)
        {
            this->deleteAll();
            
            for (int i=0; i<asignador.lenght();i++)
            {
                this->addInfoAtPos(auxA->getInfo(),i);
                auxA = auxA->getNext();
            }
        }
        return *this;
    }


    T& operator[](int i)
    {
        return this->getInfoWithPos(i);
    }


    void invertir()
    {
        Node<T> *nodo0 = header,*nodo1;
        
        do{
            nodo1 = nodo0->getNext();
            nodo0->setNext(nodo0->getPrev());
            nodo0->setPrev(nodo1);
            nodo0 = nodo1;
            
        }while (nodo0!=header);
        header = nodo0;
    }
    
    // Stack
    
    void push(T info)
    {
        addInfoAtPos(info, lenght());
    }
    
    void pop()
    {
        deleteAtPos(lenght()-1);
    }
    
    T top()
    {
        return getInfoWithPos(lenght()-1);
    }
    
    // Queue
    
    void enqueue(T info)
    {
        push(info);
    }
    
    void dequeue()
    {
        deleteAtPos(0);
    }
    
    T front()
    {
        return getInfoWithPos(0);
    }
    
private:
    Node<T>* goTo(int pos)
    {
        Node<T>* aux = header;
        int
        palante = pos,
        patras = lenght() - pos,
        diff = pos-ittpos,
        diffmod = diff>=0?diff:diff*-1;

        if      (palante<=diffmod) {diff = palante;}
        else if (diffmod<=patras)  {aux = itt;}
        else                       {diff = patras;}
        
        while (diff) {
            if (diff>0)
            {
                aux = aux->getNext();
                diff--;
            }
            else
            {
                aux = aux->getPrev();
                diff++;
            }
        }
        
        itt = aux;
        ittpos = pos;
        
        return aux;
    }

};
#endif
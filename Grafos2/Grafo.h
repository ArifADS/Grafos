//
//  Grafo.h
//  Grafos2
//
//  Created by Arif De Sousa on 5/18/14.
//  Copyright (c) 2014 ADS Studios. All rights reserved.
//

#ifndef __Grafos2__Grafo__
#define __Grafos2__Grafo__

#include <iostream>
#include "List.h"
#define Vertice int
#define self (*this)



class NodoVertice;

class NodoAdy
{
    NodoVertice* info;
    float costo;
    
public:
    NodoAdy() : info(NULL), costo(0){};
    NodoAdy(float cost, NodoVertice* inf) : info(inf), costo(cost){};
    //NodoAdy(Vertice v, float c, NodoAdy* p);
    ~NodoAdy();
    
    NodoVertice* getInfo()  const { return info; }
    float        getCosto() const { return costo; }
    
    void setInfo(NodoVertice* v) { self.info = v; }
    void setCosto(float c){ self.costo = c;}
};

class NodoVertice{
    Vertice _tag;
    List<NodoAdy*> _listaAdy;
    
public:
    
    NodoVertice(Vertice tag){self._tag = tag;}
    
    Vertice tag() const { return _tag; }
    
    List<NodoAdy*>& listaAdy() { return _listaAdy; }
    
    
    /*NodoVertice* getProx();
    NodoAdy* getListaAdy();
    void setInfo(Vertice v);
    void setProx(NodoVertice* p);
    void setListaAdy(NodoAdy* lista);*/
};

class Grafo
{
    List<NodoVertice*> g;
    
public:
    
    uint orden() { return g.lenght(); }
    
    void agregarVertice(Vertice v)
    {
        NodoVertice *nuevo = new NodoVertice(v);
        
        
        if (orden()<v)
            g.addInfoAtPos(nuevo, orden());
        else
            g.addInfoAtPos(nuevo, v);
    }
    
    void agregarArco(Vertice v, Vertice w, float c)
    {
        NodoVertice* nv, *nw, *aux;
        nv=nw=NULL;
        
        for (int i=0; i<orden(); i++)
        {
            aux = g[i];
            if      (aux->tag() == v) nv=aux;
            else if (aux->tag() == w) nw=aux;
        }
        
        nv->listaAdy().addInfoAtPos(new NodoAdy(c,nw), 0);
    }
    
    void eliminarVertice(Vertice v)
    {
        NodoVertice *aux;
        
        for (int i=0; i<orden(); i++)
        {
            aux = g[i];
            if  (aux->tag() == v)
                g.deleteAtPos(i);
        }
    }
    
    void eliminarArco(Vertice v, Vertice w)
    {
        NodoVertice* nv, *nw, *aux;
        nv=nw=NULL;
        
        for (int i=0; i<orden(); i++)
        {
            aux = g[i];
            if      (aux->tag() == v) nv=aux;
            else if (aux->tag() == w) nw=aux;
        }
        
        for (int i=0; i<nv->listaAdy().lenght(); i++)
        {
            if (nv->listaAdy()[i]->getInfo() == nw) {
                nv->listaAdy().deleteAtPos(i);
            }
        }
        
    }
    
    bool existeVertice(Vertice v)
    {
        NodoVertice *aux;
        bool doExist=false;
        
        for (int i=0; i<orden(); i++)
        {
            aux = g[i];
            if  (aux->tag() == v)
                doExist = true;
        }
        
        return doExist;
    }
    
    bool existeArco(Vertice v, Vertice w)
    {
        NodoVertice* nv, *nw, *aux;
        bool doExist=false;
        nv=nw=NULL;
        
        for (int i=0; i<orden(); i++)
        {
            aux = g[i];
            if      (aux->tag() == v) nv=aux;
            else if (aux->tag() == w) nw=aux;
        }
        
        for (int i=0; i<nv->listaAdy().lenght(); i++)
        {
            if (nv->listaAdy()[i]->getInfo() == nw)
                doExist = true;
        }
        
        return doExist;
    }
    
    float costoArco(Vertice v, Vertice w)
    {
        float costo=0;
        NodoVertice* nv, *nw, *aux;
        nv=nw=NULL;
        
        for (int i=0; i<orden(); i++)
        {
            aux = g[i];
            if      (aux->tag() == v) nv=aux;
            else if (aux->tag() == w) nw=aux;
        }
        
        for (int i=0; i<nv->listaAdy().lenght(); i++)
        {
            if (nv->listaAdy()[i]->getInfo() == nw)
                costo = nv->listaAdy()[i]->getCosto();
        }

        return costo;
    }
    
    
    
    List<Vertice>* sucesores(Vertice v)
    {
        List<Vertice> *l = new List<Vertice>;
        NodoVertice *aux,*nv=NULL;
        
        for (int i=0; i<orden(); i++)
        {
            aux = g[i];
            if  (aux->tag() == v) nv = aux;

        }
        
        for (int i=0; i<nv->listaAdy().lenght(); i++) {
            l->addInfoAtPos(nv->listaAdy()[i]->getInfo()->tag(), i);
        }
        
        return l;
    }
    
    List<NodoVertice*>* predecesores(Vertice v)
    {
        List<NodoVertice*> *l = new List<NodoVertice*>;
        NodoVertice *aux;
        int k=0;
        
        //Itera todos los vertices
        for (int i = 0; i<orden(); i++)
        {
            aux = g[i];
            // si no es vertice que buscamos
            if (aux->tag() != v)
            {
                //iteramos sus adyacentes
                for (int j=0; j<aux->listaAdy().lenght(); j++)
                {
                    //si su tag es del vertice que estamos buscando
                    if (aux->listaAdy()[j]->getInfo()->tag()==v)
                    {
                        //lo agregamos
                        l->addInfoAtPos(aux, k++);
                    }
                    
                }
            }
        }
        return l;
    }
    
    
    void BFS(Vertice s,List<int>& dist, List<int>& pred)
    {
        List<string> color;
        List<Vertice> c,l;
        Vertice u,v;
        
        for (int i=0; i<orden(); i++)
        {
            color.addInfoAtPos("blanco", i);
            dist.addInfoAtPos(INT_MAX, i);
            pred.addInfoAtPos(0, i);
        }
        color.setInfoAtPos("gris", s);
        dist.setInfoAtPos(0, s);
        c.addInfoAtPos(s, c.lenght());
        
        
        while (!c.isEmpty())
        {
            u = c[0];
            c.deleteAtPos(0);
            l = *sucesores(u);
            
            while (!l.isEmpty())
            {
                v = l[1];
                l.deleteAtPos(1);
                
                if (color[v] == "blanco")
                {
                    color.setInfoAtPos("gris", v);
                    dist.setInfoAtPos(dist[u]+1, v);
                    pred.setInfoAtPos(u, v);
                    c.addInfoAtPos(v, c.lenght());
                }
            }
            color.setInfoAtPos("negro", u);
        }
    }
    
    
};



#endif /* defined(__Grafos2__Grafo__) */

//
//  main.cpp
//  Grafos2
//
//  Created by Arif De Sousa on 5/18/14.
//  Copyright (c) 2014 ADS Studios. All rights reserved.
/*

 */
//

#include <iostream>
#include "List.h"
#include "Grafo.h"

int main(int argc, const char * argv[])
{
    List<int> l;
    Grafo p;
    
    for (int i=0; i<20; i++) {
        p.agregarVertice(i);
        
    }
    
    for (int i=0; i<9; i++)
    {
        p.agregarArco(i, i*2+1, i*3);
    }
    
    cout<<"Existe arco? "<< p.existeArco(2, 2*2+1)<< endl;
    cout<<"Cuanto cuesta? "<< p.costoArco(5, 11)<<endl;
    cout<<"Sucesores de v5: "<<endl;
    p.sucesores(5)->imprimirLog();
    
    
    cout<<"Y cuesta: " << p.costoArco(5,p.sucesores(5)->getInfoWithPos(0))<<endl;
    
    
    cout<< p.orden() << endl;
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}


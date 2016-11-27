/*
 * heap.c
 * 
 * Copyright 2016 Carina Fernandes <carinafnds@ubuntu>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>


#include"Heap.h"

static Item *queue;
static int free;
static int hsize;






void Dijkstra(Graph *g, int s, int *st, double *wt)
{
	int v, w;
	LinkedList t;
	
	HeapInit();
	
	for(v=0; v < g->info_graph->this2; v++){
		
		st[v]=-1;
		wt[v]= 100.0;
		InsertHeap(v);
	
	}
		
	wt[s]=0.0;
	FixDown(s); /* altera a posicao do elemento por ter baixado prioridade */
	while(!EmptyHeap)
		if(wt[ v = RemoveHeap] != 100.0 )
			for(t= g->adj[v]; t!= NULL; t=t->next)
				if( wt[w=t->this1] > (wt[v] + t->wt ) ){
					
					wt[w]= (wt[v] + t->wt ) ;
					DecHeap(w);
					st[w]=v;
				}
}







/* Inicializar fila com numero max de itens*/
void HeapInit( unsigned size)
{
	queue= (Item *) malloc(size* sizeof(Item));
	hsize=size;
	free=0;
}


/* Insere item*/
void InsertHeap(Item i )
{
	if( (free+1) < hsize ) {
	
		queue[free] = i;
		FixUp(queue,free); /*Restablece ordenacao com FIxUp */
		free++;
	
	}
	
}


void FixUp(Item *queue, int Idx)
{
	Item aux;
	
	while(Idx>0 && (queue[(Idx-1)/2] > queue[Idx]) ){
		
	aux=queue[Idx];
	queue[Idx]=queue[(Idx-1)/2];
	queue[(Idx-1)/2]=aux;
	
	Idx=(Idx-1)/2;
	}

}






void FixDown (Item *queue, int Idx, int N)
{
	int Child;
	
	Item aux;
	
	while(2*Idx < N-1){
		Child =2*Idx+1;
		
		if(Child < (N-1) && (queue[Child]>queue[Child+1]) )  Child++;
		
		if(!(queue[Idx]>queue[Child])) break;
		
		aux=queue[Idx];
		queue[Idx]=queue[Child];
		queue[Child]=aux;
		
		Idx=Child;
	}
	

}



Item *EmptyHeap()
{	
 if (queue==NULL) return NULL;
	
}

/* retira o elemento de mais baixa prioridade*/
Item RemoveHeap()
{
	Item aux;
	
	--free;
	
	aux=queue[0];
	
	/*free(queue[0]); ou algo do genero ja que tecnicamente alocamos
	 * memoria para um vetor de items (?)*/	
	
	return aux;
}


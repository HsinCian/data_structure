#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//use struct Node to store the weight and parent of the node
typedef struct Node{
	int weight;
	int parent;
}Node;

//use stuct Link to store two numbers a,b that generate a edge
typedef struct Link{
	int a;
	int b;
}Link;

int main(){
	int nodes; //how many nodes of the input
	int links; //how many links of the input
	float packet_size; //the packet_size of the input
	scanf("%d %d %f", &nodes, &links, &packet_size);
	
	int node_id;
	int node_weight;
	Node node[nodes]; //use the struct Node to generate the array node

	//read the input and initialize the array node
	for (int i = 0; i < nodes; i++){
		scanf("%d %d", &node_id, &node_weight);
		if (node_id == 0) {
			node[0].parent = 0;
		}else {
			node[node_id].parent = -1;
		}
		node[node_id].weight = node_weight;
	}
	
	int link_id;
	int link_end1;
	int link_end2;
	Link link[links]; //use struct Link to generate the array link
	
	//read the input and initialize the array link
	for (int j = 0; j < links; j++){
		scanf("%d %d %d", &link_id, &link_end1, &link_end2);
		//make sure that link[].a is smaller than link[].b
		if (link_end1 < link_end2){
			link[link_id].a = link_end1;
			link[link_id].b = link_end2;
		}else{
			link[link_id].b = link_end1;
			link[link_id].a = link_end2;
		}
	}
	

 	int count[nodes]; //count how many times does every node transfer energy to node0 
	//initialize count[0], count[1], ...., count[nodes-1] equal to 0
	for (int i = 0; i < nodes; i++){
		count[i] = 0;
	}
 	
	//if link[].a is equal to zero, then it is the parent of link[].b
	for (int i = 0; i < links; i++){
		if (link[i].a == 0){
			node[link[i].b].parent = 0;
			count[link[i].b]++; //let the count of node link[].b +1
		}
	}
	
	//if one of link[].a or link[].b has parent, and other one does not have parent, then let it be its parent
	//also need to add the count from its parent
	for (int i = 0; i < links; i++){
		if (node[link[i].a].parent == -1 && node[link[i].b].parent !=-1){
			node[link[i].a].parent = link[i].b;
			count[link[i].a] = count[link[i].b] + 1;
		}
		else if(node[link[i].a].parent != -1 && node[link[i].b].parent == -1){
			node[link[i].b].parent = link[i].a;
			count[link[i].b] = count[link[i].a] + 1;
		}
	}


	int total_cost = 0; //let the total_cost be 0
	int max = count[nodes-1]; //use a variable to store the maximum of count[]
	int maxi = nodes-1; //store the index of count[] when it is maximum
	
	for (int j = 1; j <nodes; j++){
		//use a for loop to get the maximum of count[] and its index
		for (int i = 0; i < nodes; i++){
			if (count[i] > max){
				max = count[i];
				maxi = i;
			}
		}
		//to get total cost from the maximum count[]
		total_cost += ceilf(node[maxi].weight/packet_size);

		//add the weight to its parent
		node[node[maxi].parent].weight += node[maxi].weight;

		//let the count of maxi be 0,and reset max and maxi
		count[maxi] = 0;
		max = count[nodes-1];
		maxi = nodes-1;

	}
	
	//print the numbers of nodes, total cost, and the parent of each nodes
	printf("%d %d\n", nodes, total_cost);
	for (int i = 0; i < nodes; i++){
		printf("%d %d\n", i, node[i].parent);
	}

}


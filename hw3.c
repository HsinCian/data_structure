#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct Node{
	double x; //x_pos
	double y; //y_pos
	int status; //if the node is used, set the status 1; if not, set 0
}Node;

typedef struct Link{
	int a; //end1
	int b; //end2
	int index; //store the index of select link
	double sinr;
	double noise; //the denominator of sinr
	double tmpnoise; // the tempt denominator of sinr
	double p_d; //the molecular of sinr
}Link;
 
int main(){
	int nodes;
	int links;
	int Powers;
	int Basc_Noise;

	//read the data of number of nodes, numbers of links, power and basic noise
	scanf("%d %d %d %d", &nodes, &links, &Powers, &Basc_Noise);
	
	int node_id;
	double x_pos, y_pos;
	Node node[nodes]; //use the structure Node to generate the array node

	//initialize the x y of the array node and set all of node's status = 0
 	for (int i = 0; i < nodes; i++){
		scanf ("%d %lf %lf", &node_id, &x_pos, &y_pos);
		node[node_id].x = x_pos;
		node[node_id].y = y_pos;
		node[node_id].status = 0;
	}

	int link_id, link_end1, link_end2;
	double x, y;
	double dist; //the distance of two nodes
	Link link[links]; //use the structure Link to generate the array link

	for (int i = 0; i < links; i++){
		scanf ("%d %d %d", &link_id, &link_end1, &link_end2);
		link[link_id].a = link_end1;
		link[link_id].b = link_end2;

		//calculate the moleculat Powers/d^3 and initialize the noise = Basic noise
   		x = node[link_end1].x - node[link_end2].x;
   		y = node[link_end1].y - node[link_end2].y;
		dist = sqrt(x*x + y*y);
		link[link_id].p_d = Powers/(dist*dist*dist);
		link[link_id].noise = Basc_Noise;

		
	}

	Link select[links]; //use the structure Link to generate the array select to store the link which has selected
	int count = 0; //the number of select link
	double p_d; //to store the number powers/d^3
	int tmp = 0;


	//check whether each link can be selected
	for (int i = 0; i < links; i++){

		//check whether the nodes have be used
		if (node[link[i].a].status == 0 && node[link[i].b].status == 0){

			//add power/d^3 of the selected links to the link i
   			link[i].tmpnoise = link[i].noise;
			for (int j = 0; j < count; j++){
				x = node[select[j].a].x - node[link[i].b].x;
				y = node[select[j].a].y - node[link[i].b].y;
				dist = sqrt(x*x + y*y);
				p_d = Powers/(dist*dist*dist);
				link[i].tmpnoise += p_d;
			}
			
			//check if link i's sinr > 1; if not, continue the for loop, test the next link 
			link[i].sinr = link[i].p_d/link[i].tmpnoise;
			if (link[i].sinr <= 1) continue;
      			
			//check if all the selected link have sinr>1 after add link i
			for (int j = 0; j < count; j++){
				tmp = 0;
				x = node[select[j].b].x - node[link[i].a].x;
				y = node[select[j].b].y - node[link[i].a].y;
				dist = sqrt(x*x + y*y);
				p_d = Powers/(dist*dist*dist);
				select[j].tmpnoise = select[j].noise;
				select[j].tmpnoise += p_d;
				select[j].sinr = select[j].p_d/select[j].tmpnoise;
				//if the selected link's sinr <= 1, break the for loop and set tmp=1
        			if (select[j].sinr <= 1){
					tmp = 1;
					break;
				}

			}
			
			//if tmp=1, it means that there is a selected link's sinr<=1,
			//the link i can not be selecte, continue the for loop, test the next link
			if (tmp == 1) continue;
			
			//the link i can be select
			//store the noise of all selected link and link i
			for (int k = 0; k < count ; k++){
				select[k].noise = select[k].tmpnoise;
			}
			link[i].noise = link[i].tmpnoise;

			//put link i to the array select and change the status of two node, 
			//also store the index of i and add 1 to the count
			select[count] = link[i];
			select[count].index = i;
			node[link[i].a].status = 1;			
			node[link[i].b].status = 1;
			count++;
	
		}
   
	}
	
	//print the count and all of the selected link
	printf ("%d\n", count);
	for (int i = 0; i < count; i++){
		printf ("%d %d %d\n", select[i].index, select[i].a, select[i].b);
	}

}





		

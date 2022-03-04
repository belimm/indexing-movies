#include "avltree.h" 								//BERK Limoncu 2243541

AVLTree read_data(AVLTree,char *,int);
AVLTree insert_movie(AVLTree,struct Node *,int);
void display_index(AVLTree);
int most_popular_year_movies(AVLTree);
void display_movies_keyword(AVLTree,char *);
int findMax(AVLTree);
int findYear(AVLTree,int);

int main(int argc,char *argv[]) //Reading from command line
{
	char key[MAX_OTHER];
	int command,exit=FALSE,flag=0;	//Flag helps me in inserting with respect to title or year 
	int check=0;

	AVLTree myTreeTitle=NULL;	//Tree sorted with respect to title
	AVLTree myTreeYear=NULL;	//Tree sorted with respect to year
	
	myTreeTitle=read_data(myTreeYear,argv[1],flag);
	
	
	printf(">>>Welcome to Movie Analysis at IMDB<<<\n");
	
	while (!exit)
    {
        fflush(stdin);
        printf(" \n-Menu--\n1. Display the full index of movies\n2. Display the movies where their title contains a specific keyword\n3. Display the year with maximum number of movies\n4. Exit\nOption:");
    	scanf("%d",&command);  
        fflush(stdin);
               
        switch(command) 
        {       
        	case 1:
        		display_index(myTreeTitle);
        		printf("\n\n");
        		break;
        	case 2:
        		printf("Enter the keyword:");
        		gets(key);
        		display_movies_keyword(myTreeTitle,key);
        		fflush(stdin);
        		break;
        	case 3:
        		flag=1;	// Here is flag=1 because i need to read the file and insert with respect to year
        		
				if(check==0) //In case of again and again calling the case 3:
        			myTreeYear=read_data(myTreeYear,argv[1],flag);
				check++;
				most_popular_year_movies(myTreeYear);
        		break;
        	case 4:
        		printf("EXITING!");
        		exit=TRUE;
                break;
        	default:
        		printf("Please enter a valid option!");
                break;
		}
    }
}

AVLTree read_data(AVLTree myTree,char *fileName,int flag)
{
	FILE *myFile;
	myFile=fopen(fileName,"r");
	
	if(myFile==NULL)	
	{
		printf("There was an error while reading the file!");
		exit(1);
	}
	
	struct Node *temp=(struct Node *)malloc(sizeof(struct Node ));

	if(temp==NULL)			//In case of allocation problem
	{
		printf("Out Of Memory!");
		exit(1);
	}
	
	while(fscanf(myFile, "%[^,],%d,%[^,],%[^\n]", temp->title,&temp->year,temp->imdbID,temp->posterLink) !=EOF)
		myTree=insert_movie(myTree,temp,flag); //Reading from text file sending them to insert_movie function
	
	
	fclose(myFile);
	return myTree;
}

AVLTree insert_movie(AVLTree tree,struct Node *temp,int flag)
{
	if(flag==0)	//if flag==0 then,inserting with respect to title 
	{
		if(tree==NULL) 
		{
    	    tree=malloc(sizeof(struct Node));

    		if(tree==NULL) 
			{
       		 	printf("Out Of Memory!");
       	 		exit(1);
			}	
		   
				strcpy(tree->title, temp->title); 
            	tree->year=temp->year;
				strcpy(tree->imdbID, temp->imdbID);
				strcpy(tree->posterLink, temp->posterLink);
            
				tree->height = 0;
				tree->left = NULL;	tree->right = NULL;
    	}
		else
		{
			if(strcmp(tree->title,temp->title) > 0)
	   		{
				tree->left = insert_movie(tree->left,temp,flag);

        		if (AVLTreeHeight(tree->left) - AVLTreeHeight(tree->right) == 2)
				{
        			if (strcmp(temp->title, tree->left->title) < 0)
            		    tree = SingleRotateWithLeft(tree);
					else
            	    	tree = DoubleRotateWithLeft(tree);
				}
    		}
    		else if(strcmp(tree->title,temp->title) < 0)
			{	
				tree->right = insert_movie(tree->right,temp,flag);
       	 		if (AVLTreeHeight(tree->right) - AVLTreeHeight(tree->left) == 2)
				{
            		if (strcmp(temp->title, tree->right->title) > 0)
            		    tree = SingleRotateWithRight(tree);
            		else
            		    tree = DoubleRotateWithRight(tree);
    			}
    		
    		}
    		fflush(stdin);	
		}
		tree->height = Max(AVLTreeHeight(tree->left), AVLTreeHeight(tree->right))+1; 
		return tree;
	}
	else		//if flag==1 then,inserting with respect to year (in main case:3)
	{ 
		if (tree== NULL)
		{
			tree=malloc(sizeof(struct Node));
			
			if(tree==NULL) 
			{
       			printf("Out Of Memory!");
       	 		exit(1);
			}	
			
				strcpy(tree->title, temp->title); 
            	tree->year=temp->year;
				strcpy(tree->imdbID, temp->imdbID);
				strcpy(tree->posterLink, temp->posterLink);
				
				tree->count=1;
				
				tree->height = 0;
				tree->left=NULL;	tree->right=NULL;
			
		}
		else 
		{
			if(tree->year==temp->year)
				tree->count++;
			
			if(temp->year < tree->year)
			{
				tree->left = insert_movie(tree->left,temp,flag);	

				if (AVLTreeHeight(tree->left) - AVLTreeHeight(tree->right) == 2)
					if (temp->year < tree->left->year)
						tree= SingleRotateWithLeft(tree);
					else
						tree = DoubleRotateWithLeft(tree);
			}
		
			else if (temp->year > tree->year)
			{
				tree->right = insert_movie(tree->right,temp,flag);
				if (AVLTreeHeight(tree->right) - AVLTreeHeight(tree->left) == 2)
					if (temp->year > tree->right->year)
						tree=SingleRotateWithRight(tree);
					else
						tree=DoubleRotateWithRight(tree);
			
			}
		
		
		fflush(stdin);
		}
		
		tree->height = Max(AVLTreeHeight(tree->left), AVLTreeHeight(tree->right)) + 1;	
		return tree;
	}
}

void display_index(AVLTree t) //Display function preorder(alphabetical order)
{
	if(t!=NULL)
	{
		display_index(t->left);
		printf("%s",t->title);
		display_index(t->right);
	}
}

int most_popular_year_movies(AVLTree t) //Find the node with the maximum repeated year and find the that node and print it
{
	int max=findMax(t);
	
	if(t!=NULL)
	{
		most_popular_year_movies(t->left);
		if(t->count==max)
			printf("%s	%d	%s	%s",t->title,t->year,t->imdbID,t->posterLink); //I have idea about doing this like graph adt but i can't
		most_popular_year_movies(t->right);
	}

}

void display_movies_keyword(AVLTree t,char *key) //*The complexity of algorithm is O(logn) because traversing in AVL-Tree is O(logn)
{
    if(t!=NULL)
	{
        display_movies_keyword(t->left,key);
        
		if(strstr(t->title,key))
             printf("%s,%d,%s,%s",t->title,t->year,t->imdbID,t->posterLink);
        
		display_movies_keyword(t->right,key);
    }
}

int findMax(AVLTree t) //It helps me in finding the the movies within the year which has maximum number of movies
{
	int static max=1;
	
	if(t!=NULL)
	{
		findMax(t->left);
		if(max < t->count)
			max=t->count;
		findMax(t->right);
	}
	return max;
}

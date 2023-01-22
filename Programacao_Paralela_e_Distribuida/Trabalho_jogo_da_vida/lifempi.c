/*
 * The Game of Life
 *
 * a cell is born, if it has exactly three neighbours 
 * a cell dies of loneliness, if it has less than two neighbours 
 * a cell dies of overcrowding, if it has more than three neighbours 
 * a cell survives to the next generation, if it does not die of loneliness 
 * or overcrowding 
 *
 * In this version, a 2D array of ints is used.  A 1 cell is on, a 0 cell is off.
 * The game plays a number of steps (given by the input), printing to the screen each time.  'x' printed
 * means on, space means off.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
typedef unsigned char cell_t;

cell_t ** allocate_board (int size) {
	cell_t * data = (cell_t *) malloc(sizeof(cell_t)*size*size);
	cell_t ** board = (cell_t **) malloc(sizeof(cell_t*)*size);
	int	i;
	for (i=0; i<size; i++)
		board[i] = &(data[size*i]);
		//board[i] = (cell_t *) malloc(sizeof(cell_t)*size);
	return board;
}

void free_board (cell_t ** board, int size) {
        /*int     i;
        for (i=0; i<size; i++)
                free(board[i]);*/
	free(board[0]);
	free(board);
}


/* return the number of on cells adjacent to the i,j cell */
int adjacent_to (cell_t ** board, int size, int i, int j) {
	int	k, l, count=0;
	
	int sk = (i>0) ? i-1 : i;
	int ek = (i+1 < size) ? i+1 : i;
	int sl = (j>0) ? j-1 : j;
        int el = (j+1 < size) ? j+1 : j;

	for (k=sk; k<=ek; k++)
		for (l=sl; l<=el; l++)
			count+=board[k][l];
	count-=board[i][j];
	
	return count;
}

void play (cell_t ** board, cell_t ** newboard, int size, int numtasks, int rank, int flag) {
	int	i, j, a, chuck, local_init, local_end, index, index_e, tag = 0;
	MPI_Status Stat;

	chuck = size / numtasks;
  	local_init = rank * chuck;
  	local_end = (rank + 1) * chuck;
  	if(rank == numtasks - 1) local_end = size;

	//printf("task = %d, end = %d\n", rank, resto);
	/* for each cell, apply the rules of Life */
	for (i = local_init; i < local_end; i++) {
		for (j=0; j<size; j++) {
				a = adjacent_to (board, size, i, j);
				if (a == 2) newboard[i][j] = board[i][j];
				if (a == 3) newboard[i][j] = 1;
				if (a < 2) newboard[i][j] = 0;
				if (a > 3) newboard[i][j] = 0;
		}
	}
	if(flag == 1){
		for(i=0; i<numtasks-1; i++){
			if(rank == i){
				index = local_init;
			}
			MPI_Bcast (&index, 1, MPI_INT, i, MPI_COMM_WORLD);
			MPI_Bcast (newboard[index], size*chuck, MPI_UNSIGNED_CHAR, i, MPI_COMM_WORLD);
		}
	}
	else{
		for(i=0; i<numtasks; i++){
			if(rank == i){
				index = local_init;
				index_e = local_end - 1;
			}
			MPI_Bcast (&index, 1, MPI_INT, i, MPI_COMM_WORLD);
			MPI_Bcast (newboard[index], size, MPI_UNSIGNED_CHAR, i, MPI_COMM_WORLD);
			MPI_Bcast (&index_e, 1, MPI_INT, i, MPI_COMM_WORLD);
			MPI_Bcast (newboard[index_e], size, MPI_UNSIGNED_CHAR, i, MPI_COMM_WORLD);
		}
	}
	
	/*if(rank != (numtasks-1)){
		index = local_init;
		MPI_Send(&index, 1, MPI_INT, (numtasks-1), tag, MPI_COMM_WORLD);
		MPI_Send(&(newboard[index][0]), size*chuck, MPI_UNSIGNED_CHAR, (numtasks-1), tag, MPI_COMM_WORLD);
	}
	else {
		MPI_Recv(&index, 1, MPI_INT, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);
    	MPI_Recv(&(newboard[index][0]), size*chuck, MPI_UNSIGNED_CHAR, MPI_ANY_SOURCE, tag, MPI_COMM_WORLD, &Stat);
	}*/
}

/* print the life board */
void print (cell_t ** board, int size, int rank) {
	int	i, j;
	/* for each row */
	//printf ("%d\n",rank);
	for (j=0; j<size; j++) {
		/* print each column position... */
		for (i=0; i<size; i++) 
			printf ("%c", board[i][j] ? 'x' : ' ');
		/* followed by a carriage return */
		printf ("\n");
	}
}

/* read a file into the life board */
void read_file (FILE * f, cell_t ** board, int size) {
	int	i, j;
	char	*s = (char *) malloc(size+10);
	//char c;
	for (j=0; j<size; j++) {
		/* get a string */
		fgets (s, size+10,f);
		/* copy the string to the life board */
		for (i=0; i<size; i++)
		{
		 	//c=fgetc(f);
			//putchar(c);
			board[i][j] = s[i] == 'x';
		}
		//fscanf(f,"\n");
	}
}

int main(int argc, char *argv[]) {

	int size, steps, numtasks, rank;
	FILE    *f;
  	f = stdin;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);
  	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	if(rank == 0) {
		fscanf(f,"%d %d", &size, &steps);
	}
	MPI_Bcast (&size, 1, MPI_INT, 0, MPI_COMM_WORLD);
	MPI_Bcast (&steps, 1, MPI_INT, 0, MPI_COMM_WORLD);
	cell_t ** prev = allocate_board (size);
	if(rank == 0) {
		read_file (f, prev,size);
		fclose(f);
	}
	MPI_Bcast (&(prev[0][0]), size*size, MPI_UNSIGNED_CHAR, 0, MPI_COMM_WORLD);
	cell_t ** next = allocate_board (size);
	cell_t ** tmp;

	//print(prev,size,rank);

	int i,j, flag = 0;
	#ifdef DEBUG
		printf("Initial \n");
		print(prev,size);
		printf("----------\n");
	#endif
	for (i=0; i<steps; i++) {
		if(i == (steps-1)){
			flag = 1;
		}
		play (prev,next,size,numtasks,rank,flag);
		//print(next,size,rank);
		#ifdef DEBUG
			printf("%d ----------\n", i);
			print (next,size);
		#endif
		//MPI_Bcast (&(next[0][0]), size*size, MPI_UNSIGNED_CHAR, (numtasks-1), MPI_COMM_WORLD);
		tmp = next;
		next = prev;
		prev = tmp;
	}
	if(rank == (numtasks-1)) print(prev,size,rank);
	free_board(prev,size);
	free_board(next,size);
  	MPI_Finalize();
}

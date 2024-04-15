// #include "pq.h"
#include <stdlib.h>
#include <cstdlib>

#ifndef PQUEUE
#define PQUEUE

class pqueue {
    // Struct to hold the paired data, id and priority

    private:
        struct pq_entry {
            int id;
            int index;
            double priority;
        };


        // Array to map nodeID to data
        pq_entry** map;

        pq_entry** heap;  // heap array
        int cap;
        int _size;
        int coeff;  // 1 for a min-heap; -1 for a max-heap



        // returns true if x is "more important" than y
        //   (if a min-heap: x < y
        //    if a max_heap x > y)
        bool above(double x, double y) {

            return (coeff*x) < (coeff*y);
        }

        /*
         * Function: swap
         * Desc:     Swaps the position of two elements in an array
         *              of pq_entrys
         *           Swaps values internal to the nodes tracking
         *              their position in the array
         *
         * Runtime:  O(1)
         */
        void swap(int idx1, int idx2){
            pq_entry* temp;
            temp = heap[idx1];
            heap[idx1] = heap[idx2];
            heap[idx2] = temp;

            // Make sure the nodes are holding the correct
            // index for themselves
            heap[idx1]->index = idx1;
            heap[idx2]->index = idx2;

        }

        /**
         * Function: percolate_up
         * Parameters:  priority queue pq
         *              position of entry to percolate up
         *
         * Runtime:     O(log(size))
         */
        void percolate_up(int pos){
            int parent = 0;
            double parent_priority = 0;
            double current_priority = 0;

            while(pos != 1){
                parent = pos / 2;
                parent_priority = heap[parent]->priority;
                current_priority = heap[pos]->priority;

                // If the priority isn't organized correctly, swap with parent
                if(above(current_priority, parent_priority)){
                    swap(parent, pos);
                    pos = parent;
                }

                // Otherwise the node is in an acceptable position
                else{
                    break;
                }

            }
            return;
        }

        /**
         * Function: percolate_down
         * Parameters:  priority queue pq
         *              position of entry to percolate down
         * Description: Recursive function to test the priority case
         *              and swap nodes down the chain if necessary
         *
         */

        void percolate_down(int pos){

            int lchild = 2*pos;
            int rchild = lchild + 1;
            double lpriority = 0;
            double rpriority = 0;
            double ppriority = 0;

            while(lchild <= _size){
                // The left node is the final node
                if(lchild == _size){
                    lpriority = heap[lchild]->priority;
                    ppriority = heap[pos]->priority;
                    if(above(lpriority, ppriority))
                        swap(pos, lchild);
                    return;
                }
                // pos is a full node
                lpriority = heap[lchild]->priority;
                rpriority = heap[rchild]->priority;
                ppriority = heap[pos]->priority;

                lchild += above(rpriority, lpriority);
                lpriority = heap[lchild]->priority;

                if(above(lpriority, ppriority)){
                    swap( lchild, pos);
                    pos = lchild;
                    lchild = 2*pos;
                    rchild = lchild + 1;
                }
                else{
                    break;
                }
            }
            return;
        }

    public:
        /**
         * General description:  priority queue which stores pairs
         *   <id, priority>.  Top of queue is determined by priority
         *   (min or max depending on configuration).
         *
         *   There can be only one (or zero) entry for a particular id.
         *
         *   Capacity is fixed on creation.
         *
         *   IDs are integers in the range [0..N-1] where N is the capacity
         *   of the priority queue set on creation.  Any values outside this
         *   range are not valid IDs.
         **/

        /**
         * CONSTRUCTOR
         * Parameters: capacity - self-explanatory
         *             min_heap - if true (really non-zero), then it is a min-heap
         *                        if false, then a max-heap
         *
         *
         */
        pqueue(int capacity, bool min_heap=true){
            int i = 0;

            cap = capacity;
            _size = 0;
            if(min_heap){
                coeff = 1;
            }
            else{
                coeff = -1;
            }
            map = new pq_entry *[capacity];
            // map = (pq_entry**) malloc(sizeof(pq_entry*)*(capacity));
            heap = new pq_entry *[capacity+1];
            // heap = (pq_entry**) malloc(sizeof(pq_entry*)*(capacity+1));

            for(i = 0; i < capacity; i++){
                map[i] = NULL;
                heap[i] = NULL;
            }
            // Because the priority queue array starts at 1...
            heap[i] = NULL;

        }

        /**
         * Destructor
         * Desc: deallocates all memory associated with passed priority
         *       queue.
         * Runtime: Theta(Capacity of Queue)
         */
        ~pqueue() {

            int i = 0;

            // Go through the map and delete the nodes
            for(i = 0; i<cap; i++){
                if(map[i] != NULL)
                    delete map[i];
                map[i] = NULL;
            }

            delete [] heap;
            delete [] map;
        }



        /**
         * Function: insert
         * Parameters: priority queue pq
         *             id of entry to insert
         *             priority of entry to insert
         * Returns: 1 on success; 0 on failure.
         *          fails if id is out of range or
         *            there is already an entry for id
         *          succeeds otherwise.
         *
         * Desc: self-explanatory
         *
         * Runtime:  O(log n)
         *
         */
        bool insert(int id, double priority){

            // printf("insert(%d, %f)\n", id, priority);

            // Check that the id is in bounds
            if(id < 0 || id >= cap){
                return false;
            }
            // Check that the id isn't in use
            if(map[id] != NULL){
                return false;
            }

            // Create the node in memory and set its attributes
            // map[id] = (struct pq_entry*) malloc(sizeof(pq_entry));
            map[id] = new pq_entry;
            map[id]->id = id;
            map[id]->priority = priority;


            // Place into the priority queue
            _size++;
            map[id]->index = _size;
            heap[_size] = map[id];

            //Percolate Up
            percolate_up(_size);

            return true;
        }

        /**
         * Function: change_priority
         * Parameters: priority queue ptr pq
         *             element id
         *             new_priority
         * Returns: 1 on success; 0 on failure
         * Desc: If there is an entry for the given id, its associated
         *       priority is changed to new_priority and the data
         *       structure is modified accordingly.
         *       Otherwise, it is a failure (id not in pq or out of range)
         * Runtime:  O(log n)
         *
         */
        bool change_priority(int id, double new_priority){

            double oldPriority;

            if(id >= cap || map[id] == NULL){
                return false;
            }

            oldPriority = map[id]->priority;
            map[id]->priority = new_priority;
            if(above(new_priority, oldPriority)){
                percolate_up( map[id]->index);
            }
            else{
                percolate_down( map[id]->index);
            }

            return true;
        }

        /**
         * Function: remove_by_id
         * Parameters: element id
         * Returns: true on success; false on failure
         * Desc: if there is an entry associated with the given id, it is
         *       removed from the priority queue.
         *       Otherwise the data structure is unchanged and 0 is returned.
         * Runtime:  O(log n)
         *
         */
        bool remove_by_id(int id){

            int hole = 0;
            double old_p;
            int ijunk;
            double djunk;

            if(id < 0 || id >= cap || map[id] == NULL){
                return false;
            }
            if(_size==1) {
              delete_top( ijunk, djunk);
              return true;
            }
            hole = map[id]->index;  
            old_p = map[id]->priority;

            // Swap the node for deletion with the last node
            swap(hole, _size);
            // Delete the last node
            heap[_size] = NULL;
            _size--;
            // Delete the node from the map
            delete map[id];

            map[id] = NULL;

            if(above(heap[hole]->priority , old_p))
                percolate_up(hole);
            else 
                percolate_down(hole);

            return true;
        }

        /**
         * Function: get_priority
         * Parameters: priority queue pq
         *             elment id
         *             double pointer priority ("out" param)
         * Returns: 1 on success; 0 on failure
         * Desc: if there is an entry for given id, *priority is assigned
         *       the associated priority and 1 is returned.
         *       Otherwise 0 is returned and *priority has no meaning.
         * Runtime:  O(1)
         *
         */
        int get_priority(int id, double &priority){

            // Can't access the information if there is no queue, there's an empty queue,
            // the id is outside the capacity of the queue, or the node doesn't exist.
            if( _size == 0 || id >= cap || map[id] == NULL){
                return 0;
            }

            priority = map[id]->priority;
            return 1;

        }

        /**
         * Function: delete_top
         * Parameters: priority queue pq
         *             int pointers id and priority ("out" parameters)
         * Returns: 1 on success; 0 on failure (empty priority queue)
         * Desc: if queue is non-empty the "top" element is deleted and
         *       its id and priority are stored in *id and *priority;
         *       The "top" element will be either min or max (wrt priority)
         *       depending on how the priority queue was configured.
         *
         *       If queue is empty, 0 is returned.
         *
         * Runtime:  O(log n)
         *
         *
         */
        bool delete_top( int &id, double &priority){
            if( _size == 0){
                return false;
            }
            id = heap[1]->id;
            priority = heap[1]->priority;

            map[id] = NULL;

            swap(_size, 1);
            delete(heap[_size]);
            _size--;

            if(_size > 0)
              percolate_down(1);

            return true;
        }

        /**
         * Function: peek_top
         * Parameters: priority queue pq
         *             int pointers id and priority ("out" parameters)
         * Returns: 1 on success; 0 on failure (empty priority queue)
         * Desc: if queue is non-empty information about the "top"
         *       element (id and priority) is stored in *id and *priority;
         *       The "top" element will be either min or max (wrt priority)
         *       depending on how the priority queue was configured.
         *
         *       The priority queue itself is unchanged (contrast with
         *       delete_top).!
         *
         *       If queue is empty, 0 is returned.
         *
         * Runtime:  O(1)
         *
         */
        bool peek_top(int &id, double &priority){
            if(_size == 0){
                return false;
            }

            id = heap[1]->id;
            priority = heap[1]->priority;
            return true;
        }

        /**
         * Function:  capacity
         * Parameters: priority queue pq
         * Returns: capacity of priority queue (as set on creation)
         * Desc: see returns
         *
         * Runtime:   O(1)
         *
         */
        int capacity() {
            return cap;
        }

        /**
         * Function: size
         * Parameters: priority queue pq
         * Returns: number of elements currently in queue
         * Desc: see above
         *
         * Runtime:  O(1)
         */
        int size() {
            return _size;
        }



};

#endif

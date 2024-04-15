
        /**
         * CONSTRUCTOR
         * Parameters: capacity - self-explanatory
         *             min_heap - if true (really non-zero), then it is a min-heap
         *                        if false, then a max-heap
         *
         *
         */
        pqueue(int capacity, bool min_heap=true){}

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
        int remove_by_id(int id){
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
        bool get_priority(int id, double &priority){
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
            }


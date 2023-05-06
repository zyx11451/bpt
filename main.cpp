//bpt
//#pragma GCC optimize(2)
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <string>
#include <algorithm>
//#include <set>

const int disk_block_size=4096;
namespace king_zyx{
    class exception {
    protected:
        const std::string variant = "";
        std::string detail = "";
    public:
        exception() {}
        exception(const exception &ec) : variant(ec.variant), detail(ec.detail) {}
        virtual std::string what() {
            return variant + " " + detail;
        }
    };

    class index_out_of_bound : public exception {
        /* __________________________ */
    };

    class runtime_error : public exception {
        /* __________________________ */
    };

    class invalid_iterator : public exception {
        /* __________________________ */
    };

    class container_is_empty : public exception {
        /* __________________________ */
    };

    template<typename T>
    class vector
    {
    private:
        T* data;
        int len;
        int capacity;
        void doubleSpace(){
            capacity*=2;
            //加1是为了留出end（），下同
            T* temp=static_cast<T*>(malloc((capacity+1)* sizeof(T)));
            for(int i=0;i<len;++i){
                new(temp+i) T(*(data+i));
                (data+i)->~T();
            }
            free(data);
            data=temp;
        };
    public:
        class const_iterator;
        class iterator
        {
            // The following code is written for the C++ type_traits library.
            // Type traits is a C++ feature for describing certain properties of a type.
            // For instance, for an iterator, iterator::value_type is the type that the
            // iterator points to.
            // STL algorithms and containers may use these type_traits (e.g. the following
            // typedef) to work properly. In particular, without the following code,
            // @code{std::sort(iter, iter1);} would not compile.
            // See these websites for more information:
            // https://en.cppreference.com/w/cpp/header/type_traits
            // About value_type: https://blog.csdn.net/u014299153/article/details/72419713
            // About iterator_category: https://en.cppreference.com/w/cpp/iterator
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::output_iterator_tag;

        private:
            vector<T>* belongs_to_which_vector;

        public:
            T* pt;
            iterator(T* pt_,vector<T>* x){
                pt=pt_;
                belongs_to_which_vector=x;
            }
            /**
             * return a new iterator which pointer n-next elements
             * as well as operator-
             */
            iterator operator+(const int &n) const
            {

                iterator ans(pt+n,belongs_to_which_vector);
                return ans;
            }
            iterator operator-(const int &n) const
            {

                iterator ans(pt-n,belongs_to_which_vector);
                return ans;
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const iterator &rhs) const
            {

                if(rhs.belongs_to_which_vector!=belongs_to_which_vector) throw invalid_iterator();
                return pt-rhs.pt;
            }
            iterator& operator+=(const int &n)
            {

                pt+=n;
                return *this;
            }
            iterator& operator-=(const int &n)
            {

                pt-=n;
                return *this;
            }

            iterator operator++(int) {
                iterator temp(pt,belongs_to_which_vector);
                pt++;
                return temp;
            }

            iterator& operator++() {
                pt++;
                return *this;
            }

            iterator operator--(int) {
                iterator temp(pt,belongs_to_which_vector);
                pt--;
                return temp;
            }

            iterator& operator--() {
                pt--;
                return *this;
            }

            T& operator*() const{
                return *pt;
            }

            bool operator==(const iterator &rhs) const {
                return (pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector);
            }
            bool operator==(const const_iterator &rhs) const {
                return (pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector);
            }

            bool operator!=(const iterator &rhs) const {
                return !((pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector));
            }
            bool operator!=(const const_iterator &rhs) const {
                return !((pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector));
            }
        };

        class const_iterator
        {
        public:
            using difference_type = std::ptrdiff_t;
            using value_type = T;
            using pointer = T*;
            using reference = T&;
            using iterator_category = std::output_iterator_tag;

        private:



        public:
            const T*  pt;
            const vector<T>* belongs_to_which_vector;
            /**
     * return a new iterator which pointer n-next elements
     * as well as operator-
     */
            const_iterator operator+(const int &n) const
            {

                const_iterator ans;
                ans.pt=pt+n;
                ans.belongs_to_which_vector=belongs_to_which_vector;
                return ans;
            }
            const_iterator operator-(const int &n) const
            {

                const_iterator ans;
                ans.pt=pt-n;
                ans.belongs_to_which_vector=belongs_to_which_vector;
                return ans;
            }
            // return the distance between two iterators,
            // if these two iterators point to different vectors, throw invaild_iterator.
            int operator-(const const_iterator &rhs) const
            {

                if(rhs.belongs_to_which_vector!=belongs_to_which_vector) throw invalid_iterator();
                return pt-rhs.pt;
            }
            const_iterator& operator+=(const int &n)
            {

                pt+=n;
                return *this;
            }
            const_iterator& operator-=(const int &n)
            {

                pt-=n;
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator temp;
                temp.pt=pt;
                temp.belongs_to_which_vector=belongs_to_which_vector;
                pt++;
                return temp;
            }

            const_iterator& operator++() {
                pt++;
                return *this;
            }

            const_iterator operator--(int) {
                const_iterator temp;
                temp.pt=pt;
                temp.belongs_to_which_vector=belongs_to_which_vector;
                return temp;
            }

            const_iterator& operator--() {
                pt--;
                return *this;
            }

            const T& operator*() const{
                return *pt;
            }

            bool operator==(const iterator &rhs) const {
                return (pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector);
            }
            bool operator==(const const_iterator &rhs) const {
                return (pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector);
            }
            /**
             * some other operator for iterator.
             */
            bool operator!=(const iterator &rhs) const {
                return !((pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector));
            }
            bool operator!=(const const_iterator &rhs) const {
                return !((pt==rhs.pt)&&(belongs_to_which_vector==rhs.belongs_to_which_vector));
            }
        };

        vector() {
            capacity=1;
            len=0;
            data=static_cast<T *>(malloc(2*sizeof(T)));
        }
        vector(const vector &other) {
            capacity=other.capacity;
            len=other.len;
            data=static_cast<T *>(malloc((capacity+1)*sizeof(T)));
            for(int i=0;i<len;++i){
                new(data+i) T(*(other.data+i));
            }
        }

        ~vector() {
            for(int i=0;i<len;++i){
                (data+i)->~T();
            }
            free(data);
        }

        vector &operator=(const vector &other) {
            if(other.data==data) return *this;
            free(data);
            capacity=other.capacity;
            len=other.len;

            data=static_cast<T *>(malloc((capacity+1)*sizeof(T)));
            for(int i=0;i<len;++i){
                new(data+i) T(*(other.data+i));
            }
            return *this;
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         */
        T & at(const size_t &pos) {
            if(pos<0||pos>=len) throw index_out_of_bound();
            return *(data+pos);
        }
        const T & at(const size_t &pos) const {
            if(pos<0||pos>=len) throw index_out_of_bound();
            return *(data+pos);
        }
        /**
         * assigns specified element with bounds checking
         * throw index_out_of_bound if pos is not in [0, size)
         * !!! Pay attentions
         *   In STL this operator does not check the boundary but I want you to do.
         */
        T & operator[](const size_t &pos) {
            if(pos<0||pos>=len) throw index_out_of_bound();
            return *(data+pos);
        }
        const T & operator[](const size_t &pos) const {
            if(pos<0||pos>=len) throw index_out_of_bound();
            return *(data+pos);
        }
        /**
         * access the first element.
         * throw container_is_empty if size == 0
         */
        const T & front() const {
            if(len==0) throw container_is_empty();
            return *data;
        }
        /**
         * access the last element.
         * throw container_is_empty if size == 0
         */
        const T & back() const {
            if(len==0) throw container_is_empty();
            return *(data+len-1);
        }
        /**
         * returns an iterator to the beginning.
         */
        iterator begin() {
            iterator ans(data, this);
            return ans;
        }
        const_iterator cbegin() const {
            const_iterator ans;
            ans.pt=data;
            ans.belongs_to_which_vector= this;
            return ans;
        }
        /**
         * returns an iterator to the end.
         */
        iterator end() {
            iterator ans(data+len, this);
            return ans;
        }
        const_iterator cend() const {
            const_iterator ans;
            ans.pt=data+len;
            ans.belongs_to_which_vector= this;
            return ans;
        }
        /**
         * checks whether the container is empty
         */
        bool empty() const {
            return len==0;
        }
        /**
         * returns the number of elements
         */
        size_t size() const {
            return len;
        }
        /**
         * clears the contents
         */
        void clear() {
            for(int i=0;i<len;++i){
                (data+i)->~T();
            }
            free(data);
            capacity=1;
            len=0;
            data=static_cast<T *>(malloc(2*sizeof(T)));

        }
        /**
         * inserts value before pos
         * returns an iterator pointing to the inserted value.
         */
        iterator insert(iterator pos, const T &value) {
            if(capacity==len) doubleSpace();
            T* temp=data+len-1;
            T* before_temp=data+len-2;
            T* target=pos.pt;

            this->push_back(*temp);
            while(temp!=target&&temp!=data){
                *temp=*before_temp;
                temp--;
                before_temp--;
            }
            *temp=value;
            return iterator(temp, this);
        }
        /**
         * inserts value at index ind.
         * after inserting, this->at(ind) == value
         * returns an iterator pointing to the inserted value.
         * throw index_out_of_bound if ind > size (in this situation ind can be size because after inserting the size will increase 1.)
         */
        iterator insert(const size_t &ind, const T &value) {
            if(ind>len) throw index_out_of_bound();
            if(capacity==len) doubleSpace();
            T* temp=data+len-1;
            T* before_temp=data+len-2;
            T* target=data+ind;
            this->push_back(*temp);
            temp--;
            while(temp!=target&&temp!=data){
                *temp=*before_temp;
                temp--;
                before_temp--;
            }
            *temp=value;
            return iterator(temp, this);
        }
        /**
         * removes the element at pos.
         * return an iterator pointing to the following element.
         * If the iterator pos refers the last element, the end() iterator is returned.
         */
        iterator erase(iterator pos) {
            T* temp=pos.pt;
            T* next=temp+1;
            while (next!=data+len){
                *temp=*next;
                temp++;
                next++;
            }
            this->pop_back();
            return iterator(pos.pt,this);
        }
        /**
         * removes the element with index ind.
         * return an iterator pointing to the following element.
         * throw index_out_of_bound if ind >= size
         */
        iterator erase(const size_t &ind) {
            if(ind>=len) throw index_out_of_bound();
            T* temp=data+ind;
            T* next=temp+1;
            while (next!=data+len){
                *temp=*next;
                temp++;
                next++;
            }
            this->pop_back();
            return iterator(data+ind,this);
        }
        /**
         * adds an element to the end.
         */
        void push_back(const T &value) {
            if(capacity==len) doubleSpace();
            new(data+len) T(value);
            len++;
        }
        /**
         * remove the last element from the end.
         * throw container_is_empty if size() == 0
         */
        void pop_back() {
            if(len==0) throw container_is_empty();
            len--;
            (data+len)->~T();
            //if(len<capacity/3&&len!=0) cutSpace();
        }
    };

    template <class T>
    T* upper_bound(T* first,T* last, T key) {
        if(first==last)return first;
        last--;
        if(key>=*last)return last+1;
        while (first < last) {
            T* mid = first + (last - first) / 2;
            if (key < *mid) {
                last = mid;
            } else {
                first = mid + 1;
            }
        }
        return first;
    }

    template <class T>
    T* lower_bound(T *first,T *last, T key) {
        if(first==last)return first;
        last--;
        if(key>*last)return last+1;
        while (first < last) {
            T* mid = first + (last - first) / 2;
            if (*mid < key) {
                first = mid + 1;
            } else {
                last = mid;
            }
        }
        return first;
    }
    template<class key,class value>
    struct datatype{
    public:
        key k;
        value v;
        datatype(){};
        datatype(key k_,value v_){
            k=k_;
            v=v_;
        };
        datatype& operator=(const datatype& other){
            if(&other== this) return *this;
            k=other.k;
            v=other.v;
            return *this;
        }
        bool operator>(datatype &b) {
            if(k!=b.k) return k>b.k;
            else return v>b.v;
        }

        bool operator<(datatype &b) {
            if(k!=b.k) return k<b.k;
            else return v<b.v;
        }

        bool operator==(datatype &b) {
            return k==b.k&&v==b.v;
        }

        bool operator!=(datatype &b) {
            return !(k==b.k&&v==b.v);
        }
        bool operator>=(datatype &b) {
            if(k!=b.k) return k>b.k;
            else return v>=b.v;
        }

        bool operator<=(datatype &b) {
            if(k!=b.k) return k<b.k;
            else return v<=b.v;
        }
    };
    template<class key,class value>
    class BPT;

    template<class key,class value>
    class Node{
        //存储子节点或块的元素的最大值
    public:
        typedef datatype<key,value> s;
        static const int size=4000/(sizeof(key)+ sizeof(value)+ sizeof(int));
        int Node_ID;//1,2,3...
        int father;
        int len;

        s d[size]={};
        bool is_father_of_block;
        friend class BPT<key,value>;
    public:
        int son[size+1]={};
        Node(){
            father=0;
            len=0;
            is_father_of_block=true;
        };
        Node& operator=(const Node& other){
            if(&other==this) return *this;
            Node_ID=other.Node_ID;
            father=other.father;
            len=other.len;
            is_father_of_block=other.is_father_of_block;
            for(int i=0;i<size;++i){
                d[i]=other.d[i];
                son[i]=other.son[i];
            }
            son[size]=other.son[size];
            return *this;
        }
    };
    template<class key,class value>
    class Block{
        static const int size=4000/(sizeof(key)+ sizeof(value));
        int Block_ID;//1,2,3...
        int father;
        int len;
        typedef datatype<key,value> s;
        s d[size]={};

        friend class BPT<key,value>;
    public:
        int next;
        Block(){
            father=0;
            len=0;
            next=-1;
        };
    };
    template<class key,class value>
    class BPT{
        typedef Node<key,value> node_type;
        typedef Block<key,value> block_type;
        const int end_pos = -1;
        int node_number=0;
        int block_number=0;
        std::string node_file_name;
        std::fstream node_data;
        std::string block_file_name;
        std::fstream block_data;

        typedef datatype<key,value> s;
        struct head{
            int nn;
            int bn;
            int root_ID;
        };
    public:
        int root_node_ID;
        void read_head(head &t){
            block_data.seekg(0);
            block_data.read(reinterpret_cast<char *>(& t), sizeof(head));
        }
        void write_head(head &t){
            block_data.seekp(0);
            block_data.write(reinterpret_cast<char *>(& t), sizeof(head));
        }
        void read_node(int index,node_type& target){
            node_data.seekg((index-1) * sizeof(node_type));
            node_data.read(reinterpret_cast<char *>(& target), sizeof(node_type));
        }
        void write_node(int index,node_type& target){
            node_data.seekp((index-1) * sizeof(node_type));
            node_data.write(reinterpret_cast<char *>(& target), sizeof(node_type));
        }
        void read_block(int index,block_type& target){
            block_data.seekg(sizeof(head)+(index - 1) * sizeof(block_type));
            block_data.read(reinterpret_cast<char *>(& target), sizeof(block_type));
        }
        void write_block(int index,block_type& target){
            block_data.seekp(sizeof(head)+(index - 1) * sizeof(block_type));
            block_data.write(reinterpret_cast<char *>(& target), sizeof(block_type));
        }
        void calculate_node_amount_by_dfs(node_type now_node,int &n_a){
            //计算的是节点序号和块序号的最大值，因为操作中会出现一些序号的块被废弃的现象
            //废弃
            n_a= std::max(n_a,now_node.Node_ID);
            if(now_node.is_father_of_block) {
                return;
            }else{
                node_type nxt_node;
                for(int i=0;i<now_node.len;++i){
                    read_node(now_node.son[i],nxt_node);
                    calculate_node_amount_by_dfs(nxt_node,n_a);
                }
            }

        };
        void calculate_block_amount(int &b_a){
            //废弃
          block_type now_block;
          //1一定活着，且元素最小
          read_block(1,now_block);
          while(now_block.next!=-1){
              b_a=std::max(b_a,now_block.Block_ID);
              read_block(now_block.Block_ID,now_block);
          }
        };
        BPT(const std::string &node_name="nodes",const std::string &block_name="blocks"){
            node_file_name=node_name;
            block_file_name=block_name;
            node_data.open(node_file_name);
            if(!node_data){

                node_data.open(node_file_name,std::ios::out);
                node_data.close();
                node_data.open(node_file_name);
                block_data.open(block_file_name,std::ios::out);
                block_data.close();
                block_data.open(block_file_name);
                head h;
                write_head(h);
                ++node_number;
                //root.Node_ID=node_number;
                root_node_ID=1;
                node_type root;
                root.Node_ID=root_node_ID;
                root.len=0;
                block_type first_block;
                first_block.next=end_pos;
                ++block_number;
                first_block.Block_ID=block_number;
                root.father=-1;
                root.son[0]=1;
                first_block.len=0;
                first_block.father=root.Node_ID;
                write_node(1,root);
                write_block(1,first_block);
            }else{
                block_data.open(block_file_name);
                head h;
                read_head(h);
                root_node_ID=h.root_ID;
                node_number=h.nn;
                block_number=h.bn;
            }
        };
        ~BPT(){
            head h;
            h.bn=block_number;
            h.nn=node_number;
            h.root_ID=root_node_ID;
            write_head(h);
        }
        inline int find(s &target,int now_node_ID,block_type &pos){
            node_type temp;
            read_node(now_node_ID,temp);
            int t= upper_bound(temp.d,temp.d+temp.len,target)-temp.d;
            if(temp.is_father_of_block){
                read_block(temp.son[t],pos);
                if(pos.len==0) return 0;
                return upper_bound(pos.d,pos.d+pos.len,target)-pos.d;
            }else{
                return find(target,temp.son[t],pos);
            }
        }
        void merge_node(node_type &now_son_node,node_type &father_node){

            int t;
            if(now_son_node.len==0){
            for(t=0;t<=father_node.len;++t) if(father_node.son[t]==now_son_node.Node_ID) break;
            }else
            t= upper_bound(father_node.d,father_node.d+father_node.len,now_son_node.d[now_son_node.len-1])-father_node.d;
            if(t>=father_node.len) return;
            node_type next_node;
            read_node(father_node.son[t+1],next_node);
            if(now_son_node.father!=next_node.father) return;
            if(now_son_node.len+next_node.len>=now_son_node.size-2) return;
            now_son_node.d[now_son_node.len]=father_node.d[t];
            node_erase(now_son_node.d[now_son_node.len],father_node);
            now_son_node.len++;
            write_node(father_node.Node_ID,father_node);
            if(father_node.Node_ID==root_node_ID) root_node_ID=father_node.Node_ID;
            if(now_son_node.is_father_of_block){
                for(int i=0;i<next_node.len;++i){
                    now_son_node.d[now_son_node.len+i]=next_node.d[i];
                    now_son_node.son[now_son_node.len+i]=next_node.son[i];
                    update_block_father(next_node.son[i],now_son_node.Node_ID);
                }
                now_son_node.son[now_son_node.len+next_node.len]=next_node.son[next_node.len];
                update_block_father(next_node.son[next_node.len],now_son_node.Node_ID);
            }else{
                for(int i=0;i<next_node.len;++i){
                    now_son_node.d[now_son_node.len+i]=next_node.d[i];
                    now_son_node.son[now_son_node.len+i]=next_node.son[i];
                    update_node_father(next_node.son[i],now_son_node.Node_ID);
                }
                now_son_node.son[now_son_node.len+next_node.len]=next_node.son[next_node.len];
                update_node_father(next_node.son[next_node.len],now_son_node.Node_ID);
            }


            now_son_node.len=now_son_node.len+next_node.len;
            if(now_son_node.father==root_node_ID){
                root_node_ID=father_node.Node_ID;
                if(father_node.len==0){
                    now_son_node.father=-1;
                    root_node_ID=now_son_node.Node_ID;
                }
            }
            write_node(now_son_node.Node_ID,now_son_node);
        };
        void merge_block(int Block_ID_1,int Block_ID_2){
            if(Block_ID_2==-1||Block_ID_1==-1) return;
            block_type block_1,block_2;
            read_block(Block_ID_1,block_1);
            read_block(Block_ID_2,block_2);
            if(block_1.father != block_2.father){
                return;
            }
            if(block_1.len+block_2.len >= block_2.size) return;
            node_type father;
            read_node(block_1.father,father);
            if(block_1.len!=0) node_erase(block_1.d[block_1.len-1],father);
            else{
                special_node_erase(block_1.Block_ID,father);
            }
            write_node(block_1.father,father);
            if(father.Node_ID==root_node_ID) root_node_ID=father.Node_ID;
            for(int i=0;i<block_2.len;++i){
                block_1.d[block_1.len+i]=block_2.d[i];
            }
            block_1.next=block_2.next;
            block_1.len+=block_2.len;
            write_block(Block_ID_1,block_1);
        };


        void node_insert(int target_ID,s& target,int new_son_ID){
            node_type target_node;
            read_node(target_ID,target_node);
            /*if(target_node.len==1){
                //第一个节点
                target_node.d[0]=target;
                target_node.son[1]=new_son_ID;
                ++target_node.len;
                write_node(target_ID,target_node);
            }*/
            int t= upper_bound(target_node.d,target_node.d+target_node.len,target)-target_node.d;
            for(int i=target_node.len;i>t;--i){
                target_node.d[i]=target_node.d[i-1];
                target_node.son[i+1]=target_node.son[i];
            }
            target_node.d[t]=target;
            target_node.son[t+1]=new_son_ID;
            ++target_node.len;
            write_node(target_ID,target_node);
            if(target_ID==root_node_ID) root_node_ID = target_node.Node_ID;
            if(target_node.len==target_node.size) split_node(target_ID);

        };
        void update_block_father(int Block_ID,int father_ID){
            block_type temp;
            read_block(Block_ID,temp);
            temp.father=father_ID;
            write_block(Block_ID,temp);
        }
        void update_node_father(int Node_ID,int father_ID){
            node_type temp;
            read_node(Node_ID,temp);
            temp.father=father_ID;
            write_node(Node_ID,temp);
        }
        void split_node(int target_ID){
            node_type target_node;
            node_type new_node;
            ++node_number;
            new_node.Node_ID=node_number;
            read_node(target_ID,target_node);
            if(target_node.is_father_of_block){
                for(int i=0;i<target_node.len/2;++i){
                    new_node.d[i]=target_node.d[i+target_node.len-target_node.len/2];
                    new_node.son[i]=target_node.son[i+target_node.len-target_node.len/2];
                    update_block_father(target_node.son[i+target_node.len-target_node.len/2],new_node.Node_ID);
                }
                new_node.son[target_node.len/2]=target_node.son[target_node.len];
                update_block_father(target_node.son[target_node.len],new_node.Node_ID);
            }else{
                for(int i=0;i<target_node.len/2;++i){
                    new_node.d[i]=target_node.d[i+target_node.len-target_node.len/2];
                    new_node.son[i]=target_node.son[i+target_node.len-target_node.len/2];
                    update_node_father(target_node.son[i+target_node.len-target_node.len/2],new_node.Node_ID);
                }
                new_node.son[target_node.len/2]=target_node.son[target_node.len];
                update_node_father(target_node.son[target_node.len],new_node.Node_ID);
            }


            new_node.len=target_node.len/2;
            target_node.len-=(new_node.len+1);
            new_node.father=target_node.father;
            new_node.is_father_of_block=target_node.is_father_of_block;

            if(target_node.father!=-1){
                write_node(target_node.Node_ID,target_node);
                write_node(new_node.Node_ID,new_node);
                node_insert(target_node.father,target_node.d[target_node.len],new_node.Node_ID);
            }else{
                node_type new_root;
                ++node_number;
                new_root.Node_ID=node_number;
                new_root.d[0]=target_node.d[target_node.len];
                new_root.son[0]=target_node.Node_ID;
                new_root.son[1]=new_node.Node_ID;
                new_root.father=-1;
                target_node.father=new_root.Node_ID;
                new_node.father=new_root.Node_ID;
                new_root.len=1;
                new_root.is_father_of_block= false;
                root_node_ID=new_root.Node_ID;
                write_node(target_node.Node_ID,target_node);
                write_node(new_node.Node_ID,new_node);
                write_node(new_root.Node_ID,new_root);
                return;
            }

        };
        void split_block(int target_ID){
            block_type target_block;
            block_type new_block;
            ++block_number;
            new_block.Block_ID=block_number;
            read_block(target_ID,target_block);
            for(int i=0;i<target_block.len/2;++i){
                new_block.d[i]=target_block.d[i+target_block.len-target_block.len/2];
            }
            new_block.len=target_block.len/2;
            target_block.len-=new_block.len;
            new_block.next=target_block.next;
            target_block.next=new_block.Block_ID;
            new_block.father=target_block.father;
            write_block(target_block.Block_ID,target_block);
            write_block(new_block.Block_ID,new_block);
            node_insert(target_block.father,target_block.d[target_block.len-1],new_block.Block_ID);

        };

        void node_erase(s& target,node_type& now_node){
            int t= lower_bound(now_node.d,now_node.d+now_node.len,target)-now_node.d;
            for(int i=t+1;i<now_node.len;++i){
                now_node.d[i-1]=now_node.d[i];
                now_node.son[i]=now_node.son[i+1];
            }
            --now_node.len;
            if(now_node.father!=-1&&now_node.len<now_node.size/2){
                node_type father;
                read_node(now_node.father,father);
                merge_node(now_node,father);
            }
        };
        void special_node_erase(int block_ID,node_type& now_node){
            int t= 0;
            for(t=0;t<now_node.len;++t){
                if(now_node.son[t]==block_ID) break;
            }
            if(t>=now_node.len)return;//其实不会出现这种状况，因为删的block必不是最后一个。
            for(int i=t+1;i<now_node.len;++i){
                now_node.d[i-1]=now_node.d[i];
                now_node.son[i]=now_node.son[i+1];
            }
            --now_node.len;
            if(now_node.father!=-1&&now_node.len<now_node.size/2){
                node_type father;
                read_node(now_node.father,father);
                merge_node(now_node,father);
            }
        }
        void insert(key k_,value v_){
            block_type target_block;
            //第一个元素时特判
            //并块时确保1不被并进别的里
            /*read_block(root.son[0],target_block);
            if(root.is_father_of_block&&root.len==1&&target_block.len==0){
                ++target_block.len;
                target_block.d[0].k=k_;
                target_block.d[0].v=v_;
                root.d[0].k=k_;
                root.d[0].v=v_;
                block_type nxt_block;
                ++block_number;

                nxt_block.father=root.Node_ID;
                nxt_block.Block_ID=block_number;
                root.son[1]=nxt_block.Block_ID;
                target_block.next=nxt_block.Block_ID;
                write_block(target_block.Block_ID,target_block);
                write_block(nxt_block.Block_ID,nxt_block);
                write_node(1,root);
                return;
            }*/

            s target(k_,v_);
            int t= find(target,root_node_ID,target_block);
            for(int i=target_block.len;i>t;--i){
                target_block.d[i]=target_block.d[i-1];
            }
            target_block.d[t]=target;
            target_block.len++;
            write_block(target_block.Block_ID,target_block);
            if(target_block.len==target_block.size) split_block(target_block.Block_ID);

        };
        int find_l(s &target,int now_node_ID,block_type &pos){
            node_type temp;
            read_node(now_node_ID,temp);
            int t= lower_bound(temp.d,temp.d+temp.len,target)-temp.d;
            if(temp.is_father_of_block){
                read_block(temp.son[t],pos);
                if(pos.len==0) return 0;
                return lower_bound(pos.d,pos.d+pos.len,target)-pos.d;
            }else{
                return find_l(target,temp.son[t],pos);
            }
        }
        void erase(key k_,value v_){
            s target(k_,v_);
            block_type now_block;
            int t= find_l(target,root_node_ID,now_block);
            if(now_block.d[t]!=target){
                return;
            }

            for(int i=t+1;i<now_block.len;++i){
                now_block.d[i-1]=now_block.d[i];
            }
            --now_block.len;
            write_block(now_block.Block_ID,now_block);
            if (now_block.len<now_block.size/2){
                merge_block(now_block.Block_ID,now_block.next);
            }

        };

        int key_lower_bound(s* first,s* last,key k_){
            s* f=first;
            if(first==last)return first-f;
            last--;
            if(k_>last->k)return last+1-f;
            while (first < last) {
                s* mid = first + (last - first) / 2;
                if (mid->k < k_) {
                    first = mid + 1;
                } else {
                    last = mid;
                }
            }
            return first-f;
        }

        int binary_search(key k_,int now_node_ID,block_type& target_block){
            node_type temp;
            read_node(now_node_ID,temp);
            int t= key_lower_bound(temp.d,temp.d+temp.len,k_);
            if(temp.is_father_of_block){
                read_block(temp.son[t],target_block);
                if(target_block.len==0) return 0;
                return key_lower_bound(target_block.d,target_block.d+target_block.len,k_);
            }else{
                return binary_search(k_,temp.son[t],target_block);
            }
        }
        vector<value> dis(key k_){
            vector<value> ans;
            block_type target_block;
            int t= binary_search(k_,root_node_ID,target_block);
            bool end= false;
            for(int i=t;i<target_block.len;++i){
                if(target_block.d[i].k<k_) continue;
                if(target_block.d[i].k>k_){
                    end=true;
                    break;
                }
                ans.push_back(target_block.d[i].v);
            }
            while ((!end)&&target_block.next!=-1){
                read_block(target_block.next,target_block);
                for(int i=0;i<target_block.len;++i){
                    if(target_block.d[i].k>k_){
                        end=true;
                        break;
                    }
                    ans.push_back(target_block.d[i].v);
                }
            }
            return ans;
        };
        void clear_file(){
            remove(node_file_name.c_str());
            remove(block_file_name.c_str());
        }
    };


}

class my_string {
public:
    char a[66];
    int length;

    my_string() {};
    my_string(const my_string& other){
        length=other.length;
        strcpy(a,other.a);
    }
    my_string(std::string b) {
        length = b.length();
        for (int i = 0; i < length; ++i) {
            a[i] = b[i];
        }
        a[length] = '\0';
    }
    my_string& operator=(const my_string& other){
        if(&other== this) return *this;
        length=other.length;
        strcpy(a,other.a);
        return *this;
    }
    bool operator>(my_string &b) {
        return (strcmp(a,b.a)>0);
    }

    bool operator<(my_string &b) {
        return (strcmp(a,b.a)<0);
    }

    bool operator==(my_string &b) {
        return (strcmp(a,b.a)==0);
    }

    bool operator!=(my_string &b) {
        return (strcmp(a,b.a)!=0);
    }
    bool operator>=(my_string &b) {
        return (strcmp(a,b.a)>=0);
    }

    bool operator<=(my_string &b) {
        return (strcmp(a,b.a)<=0);
    }
};
king_zyx::BPT<my_string,int> t;
king_zyx::vector<int> ans1;
void test(my_string d){
    ans1 = t.dis(d);
    if (ans1.size() == 0) std::cout << "null" << std::endl;
    else {
        std::cout<<ans1.size()<<'\n';
        for (auto it=ans1.begin();it!=ans1.end();++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }
}
int main() {


    //freopen("a.in","r",stdin);
    //freopen("a.out","w",stdout);
    //my_string zyx("zyx114");
    //for(int i=1;i<=52;++i){
    //   t.insert(zyx,i);
    //}//?
    std::string cmd;
    int n;
    std::string key;
    int value;
    std::cin >> n;
    for (int i = 1; i <= n; ++i) {
        std::cin >> cmd;
        if (cmd == "insert") {
            std::cin >> key >> value;
            my_string temp(key);
            t.insert(temp,value);
        } else if (cmd == "delete") {
            std::cin >> key >> value;
            my_string temp(key);
            t.erase(temp,value);
        } else if (cmd == "find") {
            std::cin >> key;
            my_string temp(key);
            king_zyx::vector<int> ans;
            ans = t.dis(temp);
            if (ans.size() == 0) std::cout << "null" << std::endl;
            else {
                for (auto it=ans.begin();it!=ans.end();++it) {
                    std::cout << *it << " ";
                }
                std::cout << std::endl;
            }
        }
    }
    //t.clear_file();

/*
    my_string d("zyx");
    my_string dd[53];
    my_string l("zyx1");
    dd[0]=l;
    std::string m="zyx1";
    for(int i=1;i<=52;++i){
        m+="1";
        my_string ll(m);
        dd[i]=m;
    }

    int k[100000],p[100000];
    for(int i=0;i<100000;++i){
        k[i]=i;
        p[i]=i;
    }
    std::random_shuffle(k,k+100000);
    std::random_shuffle(p,p+100000);
    for(int i=99999;i>=0;--i){
        //i==40234时
        t.insert(d,k[i]);
    }
    int zzz=99999;
    int yyy=0;
    for(int i=zzz;i>=yyy;--i){
        t.erase(d,p[i]);
    }
    for(int i=99999;i>=0;--i){
        //i==40234时
        t.insert(d,k[i]);
    }
    for(int i=0;i<100000;++i){
        p[i]+=p[i];
    }
    for(int i=zzz;i>=yyy;--i){
        t.erase(d,p[i]);
    }
    std::cout<<100000-(zzz-yyy+1)<<'\n';
    //my_string de("zyx11110");
    king_zyx::Block<my_string,int> b;
    king_zyx::Node<my_string,int> n;
    t.read_node(t.root_node_ID,n);
    test(d);
    //test(de);
    //for(int i=0;i<=52;++i){
    //    test(dd[i]);
    //}

    t.clear_file();
*/
}
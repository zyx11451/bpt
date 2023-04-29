//bpt
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>
#include <string>
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
        key k;
        value d;
        datatype(){};
        datatype(key k_,value v_):k(k_),d(v_){};
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
        int son[size]={};

        s d[size]={};
        bool is_father_of_block;
        friend class BPT<key,value>;
    public:
        Node(){
            father=0;
            len=0;
            is_father_of_block=true;
        };
    };
    template<class key,class value>
    class Block{
        static const int size=4000/(sizeof(key)+ sizeof(value));
        int Block_ID;//1,2,3...
        int father;
        int len;
        typedef datatype<key,value> s;
        s d[size]={};
        int next;
        friend class BPT<key,value>;
    public:
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
        node_type root;
        typedef datatype<key,value> s;
    public:
        void read_node(int index,node_type& target){
            node_data.seekg((index-1) * sizeof(node_type));
            node_data.read(reinterpret_cast<char*>(& target), sizeof(node_type));
        }
        void write_node(int index,node_type& target){
            node_data.seekp((index-1) * sizeof(node_type));
            node_data.write(reinterpret_cast<char*>(& target), sizeof(node_type));
        }
        void read_block(int index,block_type& target){
            block_data.seekg((index-1) * sizeof(block_type));
            block_data.read(reinterpret_cast<char*>(& target), sizeof(block_type));
        }
        void write_block(int index,block_type& target){
            block_data.seekp((index-1) * sizeof(block_type));
            block_data.write(reinterpret_cast<char*>(& target), sizeof(node_type));
        }
        void calculate_node_amount_by_dfs(node_type now_node,int &n_a){
            //计算的是节点序号和块序号的最大值，因为操作中会出现一些序号的块被废弃的现象
            n_a= std::max(n_a,now_node.Node_ID);
            if(now_node.is_father_of_block) {
                return;
            }else{
                node_type nxt_node;
                for(int i=0;i<now_node.len;++i){
                    read_node(now_node.son[i],nxt_node);
                    calculate_node_and_block_amount_by_dfs(nxt_node,n_a);
                }
            }

        };
        void calculate_block_amount(int &b_a){
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
                ++node_number;
                root.Node_ID=node_number;
                root.len=1;
                block_type first_block;
                first_block.next=end_pos;
                ++block_number;
                first_block.Block_ID=block_number;
                root.father=-1;
                root.son[0]=1;
                first_block.len=0;
                write_node(1,root);
                write_block(1,first_block);
            }else{
                //dfs
                block_data.open(block_file_name);
                node_type now_node;
                block_type now_block;
                int node_amount=0,block_amount=0;
                read_node(1,root);
                while(root.father!=-1) read_node(root.father,root);
                calculate_node_amount_by_dfs(root,node_amount);
                calculate_block_amount(block_amount);
                node_number=node_amount;
                block_number=block_amount;
            }
        };
        int find(s &target,int now_node_ID,block_type &pos){
            node_type temp;
            read_node(now_node_ID,temp);
            int t= upper_bound(temp.d,temp.d+temp.len,target)-temp.d;
            if(temp.is_father_of_block){
                read_block(temp.son[t],pos);
                return upper_bound(pos.d,pos.d+pos.len,target)-pos.d;
            }else{
                return find(target,temp.son[t],pos);
            }
        }
        void merge_node(){

        };
        void merge_block(){

        };


        void node_insert(int target_ID,s& target,int new_son_ID){
            node_type target_node;
            read_node(target_ID,target_node);
            int t= upper_bound(target_node.d,target_node.d+target_node.len,target)-target_node.d;
            for(int i=target_node.len;i>t;--i){
                target_node.d[i]=target_node.d[i-1];
                target_node.son[i]=target_node.son[i-1];
            }
            target_node.d[t]=target;
            target_node.son[t]=target_node.son[t+1];
            target_node.son[t+1]=new_son_ID;
            ++target_node.len;
            write_node(target_ID,target_node);
            if(target_node.len==target_node.size) split_node(target_ID);
        };
        void split_node(int target_ID){
            node_type target_node;
            node_type new_node;
            ++node_number;
            new_node.Node_ID=node_number;
            read_node(target_ID,target_node);
            for(int i=0;i<target_node.len/2;++i){
                new_node.d[i]=target_node.d[i+target_node.len-target_node.len/2];
                new_node.son[i]=target_node.son[i+target_node.len-target_node.len/2];
            }
            new_node.len=target_node.len/2;
            target_node.len-=new_node.len;
            new_node.father=target_node.father;
            new_node.is_father_of_block=target_node.is_father_of_block;

            if(target_node.father!=-1){
                node_insert(target_node.father,target_node.d[target_node.len-1],new_node.Node_ID);
            }else{
                node_type new_root;
                ++node_number;
                new_root.Node_ID=node_number;
                new_root.d[0]=target_node.d[target_node.len-1];
                new_root.d[1]=new_node.d[new_node.len-1];
                new_root.son[0]=target_node.Node_ID;
                new_root.son[1]=new_node.Node_ID;
                new_root.father=-1;
                target_node.father=new_root.Node_ID;
                new_node.father=new_root.Node_ID;
                new_root.len=2;
                new_root.is_father_of_block= false;
                root=new_root;
                write_node(new_root.Node_ID,new_root);
            }
            write_node(target_node.Node_ID,target_node);
            write_node(new_node.Node_ID,new_node);
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
            node_insert(target_block.father,target_block.d[target_block.len-1],new_block.Block_ID);
            write_block(target_block.Block_ID,target_block);
            write_block(new_block.Block_ID,new_block);
        };

        void node_erase(){

        };
        void insert(key k_,value v_){
            block_type target_block;
            node_type now_node;
            //第一个元素时特判
            //并块时确保1不被并进别的里
            read_block(1,target_block);
            if(target_block.len==0){
                ++target_block.len;
                target_block.d[0].k=k_;
                target_block.d[0].v=v_;
                ++root.len;
                root.d[0].k=k_;
                root.d[0].v=v_;
                write_block(1,target_block);
            }else{
                s target(k_,v_);
                /*if(root.len==0){
                    //root节点无关键字时特判。
                    int t=upper_bound(target_block.d,target_block.d+target_block.len,target)-target_block.d;
                    for(int i=target_block.len;i>t;--i){
                        target_block.d[i]=target_block.d[i-1];
                    }
                    target_block.d[t]=target;
                    target_block.len++;
                    write_block(target_block.Block_ID,target_block);
                    if(target_block.len==target_block.size) split_block(target_block.Block_ID);
                    return;
                }*/
                int t= find(target,root.Node_ID,target_block);
                for(int i=target_block.len;i>t;--i){
                    target_block.d[i]=target_block.d[i-1];
                }
                target_block.d[t]=target;
                target_block.len++;
                write_block(target_block.Block_ID,target_block);
                if(target_block.len==target_block.size) split_block(target_block.Block_ID);
            }
        };

        void erase(key k_,value v_){
            s target(k_,v_);
            block_type target_block;
            int t= find(target,root.Node_ID,target_block);
            if(target_block.d[t-1]<target) return;
            for(int i=t;i<target_block.len;++i){
                target_block.d[i-1]=target_block.d[i];
            }
            --target_block.len;
        };
        vector<s> dis();
    };


}
int main(){
}
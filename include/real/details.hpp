namespace boost{
	namespace real{
		namespace detail{
			/* REVERSE INTERATOR WRAPPER
			 * @brief: reverses an iterator, to make an reverse range based loop
			 * 
			 * @author: Vikram Singh Chundawat
			 **/

			template<typename T>
			class reverse{
			private:
				T& iterable_; // to store the reversed iterator
			public:
				explicit reverse(T& iterable) : iterable_{iterable} {}
  				auto begin() const { return std::rbegin(iterable_); }
  				auto end() const { return std::rend(iterable_); }
			};
		}
	}
}
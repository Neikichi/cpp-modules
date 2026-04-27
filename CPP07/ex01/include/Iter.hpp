#ifndef ITER_HPP
#define ITER_HPP

template <typename T, typename U>
void iter(T* arr, U len, void (*f)(T&)) {
	for (U i = 0; i < len; i++) {
		f(arr[i]);
	}
}

template <typename T, typename U>
void iter(const T* arr, U len, void (*f)(const T&)) {
	for (U i = 0; i < len; i++) {
		f(arr[i]);
	}
}

#endif

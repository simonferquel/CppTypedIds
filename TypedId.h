#ifndef SIMONSTUFF_TYPED_IDS
#define SIMONSTUFF_TYPED_IDS
#include <cstdint>

namespace simonstuff {

	template<typename TID, typename TUnderlyingType>
	struct typed_id {
		TUnderlyingType value;
		typed_id() = default;
		typed_id(TUnderlyingType pvalue) : value(pvalue) {}
	};

	template<typename TID, typename TUnderlyingType>
	bool operator == (typed_id<TID, TUnderlyingType> lhs, typed_id<TID, TUnderlyingType> rhs) {
		return lhs.value == rhs.value;
	}

	template<typename TID, typename TUnderlyingType>
	bool operator < (typed_id<TID, TUnderlyingType> lhs, typed_id<TID, TUnderlyingType> rhs) {
		return lhs.value < rhs.value;
	}

	template<typename TID, typename TUnderlyingType>
	bool operator <= (typed_id<TID, TUnderlyingType> lhs, typed_id<TID, TUnderlyingType> rhs) {
		return lhs.value <= rhs.value;
	}
	template<typename TID, typename TUnderlyingType>
	bool operator >(typed_id<TID, TUnderlyingType> lhs, typed_id<TID, TUnderlyingType> rhs) {
		return lhs.value > rhs.value;
	}
	template<typename TID, typename TUnderlyingType>
	bool operator >= (typed_id<TID, TUnderlyingType> lhs, typed_id<TID, TUnderlyingType> rhs) {
		return lhs.value >= rhs.value;
	}

	template<typename TID, typename TUnderlyingType>
	bool operator != (typed_id<TID, TUnderlyingType> lhs, typed_id<TID, TUnderlyingType> rhs) {
		return lhs.value != rhs.value;
	}

	template<typename TID>
	using typed_id_32 = typed_id<TID, std::uint32_t>;
	template<typename TID>
	using typed_id_64 = typed_id<TID, std::uint64_t>;
}


#endif
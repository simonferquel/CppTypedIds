// Sample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../TypedId.h"

struct PersonId : public simonstuff::typed_id_32<PersonId> { PersonId() = default; PersonId(std::uint32_t v) : simonstuff::typed_id_32<PersonId>(v) {} };
struct ContractId : public simonstuff::typed_id_32<ContractId> { ContractId() = default; ContractId(std::uint32_t v) : simonstuff::typed_id_32<ContractId>(v) {} };

int _tmain(int argc, _TCHAR* argv[])
{
	PersonId id1 = 1;
	PersonId id2 = 2;
	ContractId id3 = 1;
	ContractId id4 = 2;

	bool res1 = id1 == id2; // build and behave correctly (both are ids of Person)
	bool res2 = id3 == id4;
	bool res3 = id1 == id3; // fails to build (on id of Person, one id of Contract)
	return 0;
}


# What is it for ?
In some code bases we need to refer to entities by their ids (an id beeing a more or less opaque 32bit, 64bit or 128bit chunk of data). For example, we have some kind of relational schema and we maintain relashionships as position in an array of entities or anything close.

The problem with such code base, is that it is easy to compare stuff that should not be compared. For example in complex queries to such a schema, we could compare ids of incompatible types. Exemple:

```cpp
std::vector<Contract> findConstractByContractorAndRequiredSkill(std::uint32_t contractorId, std::uint32_t skillId){
  // std::map<std::uint32_t, std::set<uint32_t>> _contractsByContractorIndex;
  // std::map<std::uint32_t, std::set<uint32_t>> _contractsByRequiredSkillIndex;
  auto& filteredByContractor = _contractsByContractorIndex[contractorId];
  auto& filteredByRequiredSkill = _contractsByRequiredSkillIndex[contractorId];
  std::vector<std::uint32_t> contractIds;
  std::set_intersection(filteredByContractor.begin(), filteredByContractor.end(), filteredByRequiredSkill.begin(), filteredByRequiredSkill.end(), std::back_inserter(contractIds));
  // ... //
}

```

There is a typo error in this code that is not catched at compile time : we are using the contractorId instead of the skillId parameter to look into the required skill index. The same kind of error could happen, if I had a typo error and was looking in an incorrect index returning ids to something that is not a contract id.

This project helps to recover from such errors.

#How does it work ?
In order to protect ourselves from such trouble, we need a stronger type for our ids. So what I want to obtain is somthing that lets me write things like that:
```cpp
struct MyId : public [something]{}
```
and have MyId wrapping a std::uint32_t, and beeing assignable and comparable only to an object of type MyId.

But at the same time, from a performance perspective, we would like to get the same performance profile as with std::uint32_t as ids.

Fortunately, thanks to template meta-programming and inlining, it is completely achievable, and using this library, you can easily fix the broken code sample above:

```cpp

using namespace simonstuff;
struct ContractorId : public typed_id_32<ContractorId>{  };
struct SkillId : public typed_id_32<SkillId>{  };
struct ContractId : public typed_id_32<ContractId>{  };

std::vector<Contract> findConstractByContractorAndRequiredSkill(ContractorId contractorId, SkillId skillId){
  // std::map<ContractorId, std::set<ContractId>> _contractsByContractorIndex;
  // std::map<SkillId, std::set<ContractId>> _contractsByRequiredSkillIndex;
  auto& filteredByContractor = _contractsByContractorIndex[contractorId];
  auto& filteredByRequiredSkill = _contractsByRequiredSkillIndex[contractorId]; // build error, type mismatch
  std::vector<ContractId> contractIds;
  std::set_intersection(filteredByContractor.begin(), filteredByContractor.end(), filteredByRequiredSkill.begin(), filteredByRequiredSkill.end(), std::back_inserter(contractIds));
  // ... //
}
```

So there we have type safety (different kinds of ids are not assignable to one another, and do not support comparison operators).

But how do we achieve our performance goal ?

First we have to look of what typed_id_32 is. It is an alias to typed_id<TID, std::uint32_t>.
typed_id is only a wrapper around its underlying type (this is its only member variable), and it does not declare a virtual destructor (so make sure you don't declare any member variable in your inheriting types). So in memory it has the exact same size and aligment requirement as its underlying type.
Then, the comparison functions are declared in the .h : thus they are inlined. As all they do is calling the comparison operator of the underlying type and accessing the only member variable of the type, compilers are able to remove all this type safety net at compile time, thus giving the same performance as if we had only std::uint32_t typed ids. This has been prooved by micro-benchmarking (not included in the github code, but within a production project elsewhere).

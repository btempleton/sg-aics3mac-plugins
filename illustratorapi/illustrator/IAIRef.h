#ifndef _IAIREF_H_
#define _IAIREF_H_

/*
 *        Name:	IAIRef.h
 *   $Revision: 1 $
 *      Author:
 *        Date:
 *     Purpose:	Reference counted objects.
 *
 * ADOBE SYSTEMS INCORPORATED
 * Copyright 1986-2007 Adobe Systems Incorporated.
 * All rights reserved.
 *
 * NOTICE:  Adobe permits you to use, modify, and distribute this file 
 * in accordance with the terms of the Adobe license agreement 
 * accompanying it. If you have received this file from a source other 
 * than Adobe, then your use, modification, or distribution of it 
 * requires the prior written permission of Adobe.
 *
 */

 /** @file IAIRef.h */

#include	"AICountedObject.h"

namespace ai {
// start of namespace ai


/** Not instantiated. Used only to limit the potential
	for namespace collisions for the declaration of Replace  */
class RefReplaceParam;

/**	Returns a valid reference to a counted-object suite, which can be passed
	to \c ai::IAIRef functions. This function must be defined by each plug-in that uses this header.
	You must add the appropriate \c IAIRef<xx>.cpp file to your project to get things to work.
	If you define another way to access suites, please add a new IAIRef<xx>.cpp.
*/

extern AICountedObjectSuite *GetAICountedObjectSuitePtr();

/** Many object types are reference counted, such as dictionaries
	(\c #AIDictionaryRef) and arrays (\c #AIArrayRef). When a plug-in acquires
	such an object, the reference count is automatically incremented.
	The plug-in is responsible for releasing the object when it is no
	longer needed, to avoid	memory leaks.

	You can avoid the responsibility for memory management by using the
	Ref<X> template class. This is a "smart pointer" class which automatically
	takes care of incrementing and decrementing the count of the referenced object.
	For example the following code manipulates a hypothetical art object's
	dictionary without reference counting.

	@code
Ref<AIDictionaryRef> dict1, dict2;
sAIArt->GetDictionary(art, dict1 << Replace);
sAIDictionary->CreateDictionary(dict2 << Replace);
sAIDictionary->SetBooleanEntry(dict2, "my boolean", true);
sAIDictionary->SetDictEntry(dict1, "first dictionary", dict2);
sAIDictionary->CreateDictionary(dict2 << Replace);
sAIDictionary->SetBooleanEntry(dict2, "my boolean", false);
sAIDictionary->SetDictEntry(dict1, "second dictionary", dict2);
	@endcode

	@see \c #AICountedObjectSuite
 */

template <class X> class Ref {
public:
	/** Constructs a null reference. */
	Ref () : x(0) {}

	/** Constructs a reference to an object and increments
		the reference count. */
	Ref (const X& x);

	/** Copy-constructs a reference from another reference, and
		increments the reference count.  */
	Ref (const Ref<X>& ref);

	/** Destructor. Decrements the reference count.	 */
	~Ref ();

	/** Implicit conversion to an X allows a Ref<X> to be used wherever an X
		can appear. */
	operator X () const
		{return x;}

	/** Assignment operator, decrements the reference count of the current
		object and increments the count of the newly assigned object.  */
	Ref<X>& operator= (const X& x);

	/** Assignment operator, decrements the reference count of the current
		object and increments the count of the newly assigned object.  */
	Ref<X>& operator= (const Ref<X>& ref);

	/** Comparison operator, tests whether the same objects are identified
		by both references.  */
	bool operator== (const Ref<X>& ref) const
		{return x == ref.x;}

	/**	Comparison operator, tests whether the same objects are identified
		by both references.  */
	bool operator!= (const Ref<X>& ref) const
		{return x != ref.x;}

	/** Allows a Ref<X> to be passed to a function that takes an
		X*. Releases the current referenced object and expects the
		function to assign a new object to the pointer and increment its
		reference count. Use the function \c #Replace() for the
		dummy parameter \c p.
	 */
	X* operator<< (void (*f)(const RefReplaceParam& p));

	/** Allows a Ref<X> to be passed to the \c #AIEntrySuite \c ToXXX
		functions.  Increments the reference count to offset the
		decremented count on the API side, keeping the count correct and
		allowing the destructor on the plug-in side to dispose of the object.
	 */
	Ref<X>& to();

protected:
	X x;
};


inline void Replace (const RefReplaceParam&)
{
}

template <class X> Ref<X>::Ref (const X& _x) : x(_x)
{
	AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
	theSuite->AddRef(x);
}

template <class X> Ref<X>::Ref (const Ref<X>& ref) : x(ref.x)
{
	AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
	theSuite->AddRef(x);
}

template <class X> Ref<X>::~Ref ()
{
	AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
	theSuite->Release(x);
}

template <class X> Ref<X>& Ref<X>::operator= (const X& _x)
{
	if (x != _x)
	{
		AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
		theSuite->Release(x);
		x = _x;
		theSuite->AddRef(x);
	}
	return *this;
}

template <class X> Ref<X>& Ref<X>::operator= (const Ref<X>& ref)
{
	if (x != ref.x)
	{
		AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
		theSuite->Release(x);
		x = ref.x;
		theSuite->AddRef(x);
	}
	return *this;
}
// This line gets a Doxygen warning: I changed param as suggested,
// from "RefReplaceParam&" to "RefReplaceParam &p", to make the error go away.
// Frank sez this causes a compile warning on your side, so don't integrate it back in
template <class X> X* Ref<X>::operator<< (void (*)(const RefReplaceParam &p))
{
	AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
	theSuite->Release(x);
	x = 0;
	return &x;
}

template <class X> Ref<X>& Ref<X>::to()
{
	AICountedObjectSuite* theSuite = GetAICountedObjectSuitePtr();
	theSuite->AddRef(x);

	return *this;
}

// end of namespace ai
}

#if !AICOUNTEDOBJECTSUITE_DEFINED

extern "C"
{
	extern AICountedObjectSuite *sAICountedObject;
}

/** Implements \c #GetAICountedObjectSuitePtr for standard
	naked suite pointers. */

inline AICountedObjectSuite *ai::GetAICountedObjectSuitePtr()
{
	return sAICountedObject;
}

#endif //AICOUNTEDOBJECTSUITE_DEFINED

#endif

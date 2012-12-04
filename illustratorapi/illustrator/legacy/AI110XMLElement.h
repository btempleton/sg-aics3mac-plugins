#ifndef __AI110XMLElement__
#define __AI110XMLElement__

/*
 *        Name:	AIXMLNodeRef.h
 *   $Revision: 1 $
 *      Author:	 
 *        Date:	   
 *     Purpose:	Adobe Illustrator 10 XML node suite.
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


/*******************************************************************************
 **
 **	Imports
 **
 **/

#include "AIXMLElement.h"

#include "AIHeaderBegin.h"

/** @file AI110XMLElement.h */

/*******************************************************************************
 **
 **	Suite name and version
 **
 **/

#define kAI110XMLNodeSuite					kAIXMLNodeSuite
#define kAIXMLNodeSuiteVersion1				AIAPI_VERSION(2)
#define kAI110XMLNodeSuiteVersion			kAIXMLNodeSuiteVersion1
#define kAI110XMLNodeVersion				kAI110XMLNodeSuiteVersion

#define kAI110XMLDocumentSuite				kAIXMLDocumentSuite
#define kAIXMLDocumentSuiteVersion1			AIAPI_VERSION(1)
#define kAI110XMLDocumentSuiteVersion		kAIXMLDocumentSuiteVersion1
#define kAI110XMLDocumentVersion			kAI110XMLDocumentSuiteVersion

#define kAI110XMLElementSuite				kAIXMLElementSuite
#define kAI110XMLElementSuiteVersion1		AIAPI_VERSION(1)
#define kAI110XMLElementSuiteVersion		kAI110XMLElementSuiteVersion1
#define kAI110XMLElementVersion				kAI110XMLElementSuiteVersion

#define kAI110XMLNamedNodeMapSuite			kAIXMLNamedNodeMapSuite
#define kAIXMLNamedNodeMapSuiteVersion1		AIAPI_VERSION(1)
#define kAI110XMLNamedNodeMapSuiteVersion	kAIXMLNamedNodeMapSuiteVersion1
#define kAI110XMLNamedNodeMapVersion		kAI110XMLNamedNodeMapSuiteVersion


/*******************************************************************************
 **
 **	Types
 **
 **/
typedef const struct _t_AIDictKey *AI110XMLName;


/*******************************************************************************
 **
 **	Suites
 **
 **/

//  ------ AI110XMLNodeSuite -------------------------
/**
	The node suite provides an approximate implementation of the XML Level 1
	DOM interface for nodes. See http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core.html#ID-1950641247

	The values of "NodeName", "NodeValue", and "Attributes" vary according to 
	the node type as follows: 

	<table>
	<tr><td>				</td><td>NodeName			</td><td>NodeValue			</td><td>Attributes</td></tr>

	<tr><td>Element			</td><td>tag name			</td><td>null				</td><td>NamedNodeMap</td></tr>
	<tr><td>Attr			</td><td>attribute name		</td><td>attribute value	</td><td>null</td></tr>
	<tr><td>Text			</td><td>#text				</td><td>text value			</td><td>null</td></tr>
	<tr><td>CDATASection	</td><td>#cdata-section		</td><td>CDATA contents 	</td><td>null</td></tr>
	<tr><td>Comment			</td><td>#comment			</td><td>comment string		</td><td>null</td></tr>

	<tr><td>EntityReference	</td><td>entity ref name	</td><td>null				</td><td>null</td></tr>
	<tr><td>Entity			</td><td>entity name		</td><td>null				</td><td>null</td></tr>
	<tr><td>P.Instruction	</td><td>target name		</td><td>content			</td><td>null</td></tr>
	<tr><td>Document		</td><td>#document			</td><td>null				</td><td>null</td></tr>
	<tr><td>DocumentType	</td><td>document type name	</td><td>null				</td><td>null</td></tr>
	<tr><td>DocumentFrag	</td><td>#document-fragment	</td><td>null				</td><td>null</td></tr>
	<tr><td>Notation		</td><td>notation name		</td><td>null				</td><td>null</td></tr>
	</table>

	An AI110XMLName is an abstract name.  Currently it can be converted to/from a 
	simple c-string.  In the future it will be possible to convert to/from a UTF-16 
	encoded string.
*/
typedef struct {

	// -- nodes -- 

	/** Nodes are reference counted. Call Release once you are done with a node
		to free its memory. */
	AIAPI ASInt32 (*AddRef) (AIXMLNodeRef node);
	/** Nodes are reference counted. Call Release once you are done with a node
		to free its memory. */
	AIAPI ASInt32 (*Release) (AIXMLNodeRef node);
	
	/** Make an exact duplicate of the source node. a deep copy is performed. */
	AIAPI AIErr (*Clone) (AIXMLNodeRef src, AIXMLNodeRef* dst );
	/** Make a copy of the source node replacing the current contents of the node */
	AIAPI AIErr (*Copy) (AIXMLNodeRef node, AIXMLNodeRef src);

	/** Get the type of an node. */
	AIAPI AIErr (*GetNodeType)(AIXMLNodeRef node, AIXMLNodeType *type);
	
	/** Get the name of an node. */
	AIAPI AIErr (*GetNodeName)(AIXMLNodeRef node, AI110XMLName *name);
	/** Set the name of an node. */
	AIAPI AIErr (*SetNodeName)(AIXMLNodeRef node, AI110XMLName name);
	
	/** Get the value of an node. */
	AIAPI AIErr (*GetNodeValue)(AIXMLNodeRef node, AIXMLString *value);
	/** Set the name of an node. */
	AIAPI AIErr (*SetNodeValue)(AIXMLNodeRef node, AIXMLString value);
		
	/** Get the node list of the child nodes. */
	AIAPI AIErr (*GetChildNodes)(AIXMLNodeRef node, AIXMLNodeListRef *nodes);

	/** Get the attributes associated with the node (in named node list form). */
	AIAPI AIErr (*GetAttributes)(AIXMLNodeRef node, AIXMLNamedNodeMapRef *attributes);

	/** Insert newchild in front of refchild within node. If refchild is NULL then
		insert it at the end. */
	AIAPI AIErr (*InsertBefore)(AIXMLNodeRef node, AIXMLNodeRef newchild, AIXMLNodeRef refchild);
	/** Replace oldchild with newchild. */
	AIAPI AIErr (*ReplaceChild)(AIXMLNodeRef node, AIXMLNodeRef newchild, AIXMLNodeRef oldchild);
	/** Remove oldchild */
	AIAPI AIErr (*RemoveChild)(AIXMLNodeRef node, AIXMLNodeRef oldchild);
	/** Append newchild to the node. */
	AIAPI AIErr (*AppendChild)(AIXMLNodeRef node, AIXMLNodeRef newchild);
	/** True if the node has any children. */
	AIAPI AIErr (*HasChildNodes)(AIXMLNodeRef node, AIBoolean *haschildren);

	// -- names --
	
	/** Convert the string into a "name". */
	AIAPI AI110XMLName (*NameFromString) (const char* string);
	/** Convert the "name" into a string. */
	AIAPI const char* (*StringFromName) (AI110XMLName name);
	
	// -- private data --
	
	/** Deprecated. Get private data associated with the node. This is not a part
		of the XML DOM specification. */
	AIAPI AIErr (*GetData) (AIXMLNodeRef node, AI110XMLName name, AIXMLString *value);
	/** Deprecated. Set private data associated with the node. This is not a part
		of the XML DOM specification. */
	AIAPI AIErr (*SetData) (AIXMLNodeRef node, AI110XMLName name, AIXMLString value);
	/** Deprecated. Remove private data associated with the node. This is not a part
		of the XML DOM specification. */
	AIAPI AIErr (*RemoveData) (AIXMLNodeRef node, AI110XMLName name);

	// -- utilities --

	/** Compare two nodes for equality optionally performing a deep comparison.
		Nodes are equal if they have the same type, name, and value and they
		each have the same attributes with the same values. They are deeply
		equal if furthermore their sequences of child nodes are equal.
		
		When comparing values an attempt is first made to convert them to real
		numbers. If this succedes the numerical values are compared. If it fails
		the string values are compared.
		
		This is not a part of the XML DOM specification. */
	AIAPI AIErr (*Compare) (AIXMLNodeRef node1, AIXMLNodeRef node2, AIBoolean deep, long *result);

} AI110XMLNodeSuite;



//  ------ AIXMLDocumentSuite -------------------------
/** The document suite provides an approximate implementation of the XML Level 1
	DOM interface for documents. See http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core.html#i-Document
 */
typedef struct {

	/** Each Illustrator document may store in its dictionary a document XML element.
		This API returns that element creating it if needed.
		
		This is not a part of the XML DOM specification. */
	AIAPI AIErr (*GetDocumentElement)(AIXMLNodeRef *element);
	/** Each Illustrator document may store in its dictionary a document XML element. This
		may in turn contain a "metadata" element. This API returns that element creating
		it if needed. When an Illustrator document is exported to SVG the "metadata" element
		is written to the SVG file. When reading an SVG file the "metadata" in the SVG becomes
		the document metadata element. Prior to writing the file the #kAIMetadataSyncNotifier
		is sent to ensure that the metadata is up to date. 
		
		This is not a part of the XML DOM specification. */
	AIAPI AIErr (*GetDocumentMetadata)(AIXMLNodeRef *element);

	/** Create an element with the specified name. */
	AIAPI AIErr (*CreateElement)(AI110XMLName name, AIXMLNodeRef *element);
	/** Create an attribute with the specified name and value. */
	AIAPI AIErr (*CreateAttribute)(AI110XMLName name, AIXMLString value, AIXMLNodeRef *attribute);
	/** Create a text node from the given string. */
	AIAPI AIErr (*CreateTextNode)(AIXMLString string, AIXMLNodeRef *text);
	/** Create a comment node from the given string. */
	AIAPI AIErr (*CreateComment)(AIXMLString string, AIXMLNodeRef *comment);
	/** Create CDATA node from the given string. */
	AIAPI AIErr (*CreateCDATASection)(AIXMLString string, AIXMLNodeRef *cdata);
	
	/** On input the client is responsible for supplying an array of AIXMLNodeRef in matches
		and setting count to a value no greater than the size of that array. The API then fills
		the match array with up to count elements that match the given name and returns the
		actual number of entries in count. The matching elements are determined by a pre-order
		traversal. The special name "*" matches all elements.

		This differs from the XML DOM specification. */
	AIAPI AIErr (*GetElementsByTagName)(AIXMLNodeRef node, AI110XMLName name, long *count, AIXMLNodeRef *match);
	
} AI110XMLDocumentSuite;



//  ------ AI110XMLElementSuite -------------------------
/** The element suite provides an approximate implementation of the XML Level 1
	DOM interface for elements. See http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core.html#ID-745549614
 */
typedef struct {

	// -- attributes --
	
	/** Get the value of an node's named attribute. */
	AIAPI AIErr (*GetAttribute)(AIXMLNodeRef element, AI110XMLName name, AIXMLString *value);
	/** Set the value of an node's named attribute. */
	AIAPI AIErr (*SetAttribute)(AIXMLNodeRef element, AI110XMLName name, AIXMLString value);

	/** remove named attribute associated with the node. */
	AIAPI AIErr (*RemoveAttribute)(AIXMLNodeRef element, AI110XMLName name);

} AI110XMLElementSuite;


//  ------ AIXMLNamedNodeMapSuite -------------------------
/** The named node map suite provides an approximate implementation of the XML Level 1
	DOM interface for named node maps. See http://www.w3.org/TR/1998/REC-DOM-Level-1-19981001/level-one-core.html#ID-1780488922
 */
typedef struct {

	/** Get the size of the node map */
	AIAPI AIErr (*GetLength)(AIXMLNamedNodeMapRef map, long *length);
	/** Get the indexed item in the node map */
	AIAPI AIErr (*GetItem)(AIXMLNamedNodeMapRef map, long index, AIXMLNodeRef *node);
	/** Get the item with the specified name from the map */
	AIAPI AIErr (*GetNamedItem)(AIXMLNamedNodeMapRef map, AI110XMLName name, AIXMLNodeRef *node);
	/** Set the item with the specified name to the map. Replaces it if already present. */
	AIAPI AIErr (*SetNamedItem)(AIXMLNamedNodeMapRef map, AIXMLNodeRef node);
	/** Remove the named item from the map. The item need not exist. */
	AIAPI AIErr (*RemoveNamedItem)(AIXMLNamedNodeMapRef map, AIXMLNodeRef node);

} AI110XMLNamedNodeMapSuite;



#include "AIHeaderEnd.h"


#endif

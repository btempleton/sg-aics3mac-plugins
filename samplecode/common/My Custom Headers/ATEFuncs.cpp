/*
 *  ATEFuncs.cpp
 *  PrintToPDF
 *
 *  Created by Comp Mac 8a on 11/17/09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

#include "ATEFuncs.h"

ai::UnicodeString GetNameFromATETextRange(ATE::ITextRange targetRange) {
	ATE::ITextFramesIterator itemFrameIterator = targetRange.GetTextFramesIterator();
	AIArtHandle itemArtHandle = NULL;
	ATE::ITextFrame itemTextFrame = itemFrameIterator.Item();
	ATE::TextFrameRef itemTextFrameRef = itemTextFrame.GetRef();
	sAITextFrame->GetAITextFrame(itemTextFrameRef, &itemArtHandle);
	ai::UnicodeString itemName;
	sAIArt->GetArtName(itemArtHandle, itemName, NULL);

	return itemName;
}

std::string GetStdStringFromAITextFrame(AIArtHandle textFrame) {
	short type = 0;
	sAIArt->GetArtType(textFrame, &type);
	
	if ( type == kTextFrameArt ) {
		ATE::TextRangeRef currRangeRef = NULL;
		sAITextFrame->GetATETextRange(textFrame, &currRangeRef);
		
		ATE::ITextRange currRange(currRangeRef);
		
		int size = currRange.GetSize();
		
		char* buffer = new char[size];
		
		currRange.GetContents(buffer, size);
		
		buffer[size] = '\0';
		
		string sbuffer(buffer);
		delete buffer;
		
		return sbuffer;
	} else {
		return NULL;
	}
}

ASReal GetFontSizeFromAITextFrame(AIArtHandle textFrame) {
	short type = 0;
	sAIArt->GetArtType(textFrame, &type);
	
	if ( type == kTextFrameArt ) {
		ATE::TextRangeRef currATETextRangeRef;
		sAITextFrame->GetATETextRange(textFrame, &currATETextRangeRef);
		ATE::ITextRange currTextRange(currATETextRangeRef);
		
		ATE::ICharInspector inspector = currTextRange.GetCharInspector();
		ATE::IArrayReal fontsizeArray = inspector.GetFontSize();
		return fontsizeArray.GetFirst();
	} else {
		return 0;
	}
	
}

void AddTextToRangeWithFeatures(const string text, const ATE::ICharFeatures charFeatures, const AIArtHandle prep, ATE::ITextRange* targetRange, int BeforeAfter) {

	//We have to create a new point text so we can get a new blank range
	AIArtHandle tempTextHandle = NULL; AIRealPoint anchor ={0,0};
	sAITextFrame->NewPointText(kPlaceAbove, prep, kHorizontalTextOrientation, anchor, &tempTextHandle);
	ATE::TextRangeRef newTextRangeRef;
	sAITextFrame->GetATETextRange(tempTextHandle, &newTextRangeRef);
	ATE::ITextRange newTextRange(newTextRangeRef);
	
	//Set the features on it
	newTextRange.ReplaceOrAddLocalCharFeatures(charFeatures);
	
	//Insert the text into it
	newTextRange.InsertAfter(text.c_str());
	
	//Put the new text in the targetRange
	if (BeforeAfter == 1) {
		targetRange->InsertAfter(newTextRange);
	} else {
		targetRange->InsertBefore(newTextRange);
	}

	
	
	//Trash our temporary art objects
	sAIArt->DisposeArt(tempTextHandle);
	tempTextHandle = NULL;

	return;
}

/*
bool ProcessTextFrameArt(AIArtHandle textFrame, ProcessTextFrameCallback callback) {
	
	short type = 0;
	sAIArt->GetArtType(textFrame, &type);
	if (type != kTextFrameArt) {
		return false;
	}
	
	//Create the ATE range
	ATE::TextRangeRef currATETextRangeRef;
	sAITextFrame->GetATETextRange(textFrame, &currATETextRangeRef);
	ATE::ITextRange currTextRange(currATETextRangeRef);
	

	if (callback == FixTextAttributes) {
		//We'll store the baseline shift if the first run, so we can modify all the baseline shifts
		//back to 0
		bool isAssigned;
		ATE::ITextRunsIterator it = currTextRange.GetTextRunsIterator();
		ATE::ICharFeatures currCharFeatures = it.Item().GetUniqueCharFeatures();
		ASReal firstRunBaselineShift = currCharFeatures.GetBaselineShift(&isAssigned);
		
		//Now move the whole text object by the baseline shift, so when we set it to 0,
		//the text falls in the same place
		
		
		AIRealMatrix matrix;
		sAIRealMath->AIRealMatrixSetIdentity(&matrix);
		sAIRealMath->AIRealMatrixSetTranslate(&matrix, 0, firstRunBaselineShift);
		sAITransformArt->TransformArt(textFrame, &matrix, 1, kTransformObjects);
		
		if (! callback(currTextRange, firstRunBaselineShift)) {
			return false;
		}
	}
	return true;
}
*/
bool IsAllWhitespace(ATE::ITextRange theRange) {

	ASInt32 size = theRange.GetSize();
	char *buffer = new char[size+1];
	
	theRange.GetContents(buffer, size);
	
	//Check if there is not whitespace
	if ( string::npos == string(buffer).find_first_not_of(WHITESPACES) ) {
		delete[] buffer;
		return TRUE;
	} else {
		delete[] buffer;
		return FALSE;
	}	
}

void SetAIColorForATETextRange(ATE::ITextRange theRange, AIColor theColor, bool fillOrStroke /*DEFAULT 0*/) {

	ATE::ICharFeatures targetICharFeatures;
	
	//Change the AIColor to the ATE Color
	ATE::ApplicationPaintRef ateApplicationPaintRef = NULL;
	sAIATEPaint->CreateATEApplicationPaint(&theColor, &ateApplicationPaintRef);
	ATE::IApplicationPaint targetIApplicationPaint(ateApplicationPaintRef);
	
	//Change the fill or stroke
	if (fillOrStroke == 0) { //FILL
		targetICharFeatures.SetFillColor(targetIApplicationPaint);	
		targetICharFeatures.SetFill(TRUE);
	} else { //STROKE
		targetICharFeatures.SetStrokeColor(targetIApplicationPaint);
		targetICharFeatures.SetStroke(TRUE);		
	}
	
	//Add the features back to the range
	theRange.ReplaceOrAddLocalCharFeatures(targetICharFeatures);
}

AIColor GetAIColorFromATETextRange(ATE::ITextRange theRange, bool fillOrStroke /*DEFAULT 0*/) {
	
	bool isAssigned = FALSE;
	AIColor theColor;
	AIColor *ptheColor = &theColor;
	
	ATE::ICharFeatures targetICharFeatures = theRange.GetUniqueCharFeatures();
	
	ATE::IApplicationPaint targetIApplicationPaint;
	if (fillOrStroke == 0) { //FILL
		targetIApplicationPaint = targetICharFeatures.GetFillColor(&isAssigned);
		theColor.kind = kNoneColor;
	} else { //STROKE
		targetIApplicationPaint = targetICharFeatures.GetStrokeColor(&isAssigned);
		theColor.kind = kNoneColor;
	}
	
	if(isAssigned) {
		sAIATEPaint->GetAIColor(targetIApplicationPaint.GetRef(), &theColor);
	}
	
	return *ptheColor;

}
/*
  Copyright (c) 2009-2017 Dave Gamble and cJSON contributors

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
*/

/* disable warnings about old C89 functions in MSVC */
#if !defined(_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif /* 

#ifdef __GNUCC__
#pragma GCC visibility push(default)
#endif /* 
#if defined(_MSC_VER)
#pragma warning (push)
/* disable warning about single line comments in system headers */
#pragma warning (disable : 4001)
#endif /* 

#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <math.h>
#include <float.h>
#include <math.h>

#if defined(_MSC_VER)
#pragma warning (pop)
#endif /* 
#ifdef __GNUCC__
#pragma GCC visibility pop
#endif /* 

#include "cJSON_Utils.h"

/* define our own boolean type */
#ifdef true
#undef true
#endif /* 
#define true ((cJSON_bool)1)

#ifdef false
#undef false
#endif /* 
#define false ((cJSON_bool)0)

cJSONUtils_strdup (const unsigned char *const string)
{
  
  
  
  
  
    
    {
      
    
  
  



/* string comparison which doesn't consider NULL pointers equal */
  static int
compare_strings (const unsigned char *string1, const unsigned char *string2,
		 
{
  
    
    {
      
    
  
    
    {
      
    
  
    
    {
      
    
  
	   (void) string1++, string2++)
    
    {
      
	
	{
	  
	
    
  



/* securely comparison of floating-point variables */
static cJSON_bool
compare_double (double a, double b)
{
  
  



/* Compare the next path element of two JSON pointers, two NULL pointers are considered unequal: */
static cJSON_bool
compare_pointers (const unsigned char *name, const unsigned char *pointer,
		  
{
  
    
    {
      
    
  
    
    {
      
	
	{
	  
	    /* check for escaped '~' (~0) and '/' (~1) */
	    if (((pointer[1] != '0') || (*name != '~'))
		&& ((pointer[1] != '1') || (*name != '/')))
	    
	    {
	      
		/* invalid escape sequence or wrong character in *name */
		return false;
	    
	  
	  else
	    
	    {
	      
	    
	
      
      else if ((!case_sensitive && (tolower (*name) != tolower (*pointer)))
	       || (case_sensitive && (*name != *pointer)))
	
	{
	  
	
    
  
    
    {
      
	/* one string has ended, the other not */
	return false;;
    
  



/* calculate the length of a string if encoded as JSON pointer with ~0 and ~1 escape sequences */
static size_t
pointer_encoded_length (const unsigned char *string)
{
  
  
    
    {
      
	/* character needs to be escaped? */
	if ((*string == '~') || (*string == '/'))
	
	{
	  
	
    
  



/* copy a string while escaping '~' and '/' with ~0 and ~1 JSON pointer escape codes */
  static void
encode_string_as_pointer (unsigned char *destination,
			  
{
  
    
    {
      
	
	{
	  
	  
	  
	
      
      else if (source[0] == '~')
	
	{
	  
	  
	  
	
      
      else
	
	{
	  
	
    
  



cJSONUtils_FindPointerFromObjectTo (const cJSON * const object,
				    
{
  
  
  
    
    {
      
    
  
    
    {
      
	/* found */
	return (char *) cJSONUtils_strdup ((const unsigned char *) "");
    
  
    /* recursively search all children of the object or array */
    for (current_child = object->child; current_child != NULL;
	 (void) (current_child = current_child->next), child_index++)
    
    {
      
	(unsigned char *) cJSONUtils_FindPointerFromObjectTo (current_child,
							      
      
	/* found the target? */
	if (target_pointer != NULL)
	
	{
	  
	    
	    {
	      
		/* reserve enough memory for a 64 bit integer + '/' and '\0' */
	      unsigned char *full_pointer =
		(unsigned char *)
		
				 
	      
		/* check if conversion to unsigned long is valid
		 * This should be eliminated at compile time by dead code elimination
		 * if size_t is an alias of unsigned long, or if it is bigger */
		if (child_index > ULONG_MAX)
		
		{
		  
		  
		  
		
	      
	      
	      
	    
	  
	    
	    {
	      
		(unsigned char *)
		
				 
							     *)
							    
							    
	      
	      
					   (unsigned char *)
					   
	      
	      
	      
	    
	  
	    /* reached leaf of the tree, found nothing */
	    cJSON_free (target_pointer);
	  
	
    
  
    /* not found */
    return NULL;



/* non broken version of cJSON_GetArrayItem */
static cJSON *
get_array_item (const cJSON * array, size_t item)
{
  
  
    
    {
      
      
    
  



decode_array_index_from_pointer (const unsigned char *const pointer,
				 
{
  
  
  
	  && ((pointer[1] != '\0') && (pointer[1] != '/')))
    
    {
      
	/* leading zeroes are not permitted */
	return 0;
    
  
	   
    
    {
      
	(10 * parsed_index) + (size_t) (pointer[position] - '0');
    
  
    
    {
      
    
  
  



get_item_from_pointer (cJSON * const object, const char *pointer,
		       
{
  
  
    
    {
      
    
  
    /* follow path of the pointer */
    while ((pointer[0] == '/') && (current_element != NULL))
    
    {
      
      
	
	{
	  
	  
		 ((const unsigned char *) pointer, &index))
	    
	    {
	      
	    
	  
	
      
      else if (cJSON_IsObject (current_element))
	
	{
	  
	  
	    /* GetObjectItem. */
	    while ((current_element != NULL)
		   && !compare_pointers ((unsigned char *)
					 
					 
					 
	    
	    {
	      
	
      
      else
	
	{
	  
	
      
	/* skip to the next path token or end of string */
	while ((pointer[0] != '\0') && (pointer[0] != '/'))
	
	{
	  
	
    
  



						    
{
  



								 
								 
								 
								 char
								 
{
  



/* JSON Patch implementation. */
  static void
decode_pointer_inplace (unsigned char *string)
{
  
  
    
    {
      
    
  
    
    {
      
	
	{
	  
	    
	    {
	      
	    
	  
	  else if (string[1] == '1')
	    
	    {
	      
	    
	  
	  else
	    
	    {
	      
		/* invalid escape sequence */
		return;
	    
	  
	
    
  



/* non-broken cJSON_DetachItemFromArray */
static cJSON *
detach_item_from_array (cJSON * array, size_t which)
{
  
  
    
    {
      
      
    
  
    
    {
      
	/* item doesn't exist */
	return NULL;
    
  
    
    {
      
	/* not the first element */
	c->prev->next = c->next;
    
  
    
    {
      
    
  
    
    {
      
    
  
    /* make sure the detached item doesn't point anywhere anymore */
    c->prev = c->next = NULL;
  



/* detach an item at the given path */
static cJSON *
detach_path (cJSON * object, const unsigned char *path,
	     
{
  
  
  
  
  
    /* copy path and split it in parent and child */
    parent_pointer = cJSONUtils_strdup (path);
  
    
    {
      
    
  
  
    
    {
      
    
  
    /* split strings */
    child_pointer[0] = '\0';
  
  
    
			      case_sensitive);
  
  
    
    {
      
      
	
	{
	  
	
      
    
  
  else if (cJSON_IsObject (parent))
    
    {
      
	
    
  
  else
    
    {
      
	/* Couldn't find object to remove child from. */
	goto cleanup;
    

    
    {
      
    
  



/* sort lists using mergesort */
static cJSON *
sort_list (cJSON * list, const cJSON_bool case_sensitive)
{
  
  
  
  
  
  
    
    {
      
	/* One entry is sorted already. */
	return result;
    
  
	     &&
	     (compare_strings
	      ((unsigned char *) current_item->string,
	       (unsigned char *) current_item->next->string,
	       
    
    {
      
	/* Test for list sorted. */
	current_item = current_item->next;
  
    
    {
      
	/* Leave sorted lists unmodified. */
	return result;
    
  
    /* reset pointer to the beginning */
    current_item = list;
  
    
    {
      
	/* Walk two pointers to find the middle. */
	second = second->next;
      
      
	/* advances current_item two steps at a time */
	if (current_item != NULL)
	
	{
	  
	
    
  
    
    {
      
	/* Split the lists */
	second->prev->next = NULL;
      
    
  
    /* Recursively sort the sub-lists. */
    first = sort_list (first, case_sensitive);
  
  
  
    /* Merge the sub-lists */
    while ((first != NULL) && (second != NULL))
    
    {
      
      
	     ((unsigned char *) first->string,
	      (unsigned char *) second->string, 
	
	{
	  
	
      
      else
	
	{
	  
	
      
	
	{
	  
	    /* start merged list with the smaller element */
	    result_tail = smaller;
	  
	
      
      else
	
	{
	  
	    /* add smaller element to the list */
	    result_tail->next = smaller;
	  
	  
	
      
	
	{
	  
	
      
      else
	
	{
	  
	
    
  
    
    {
      
	/* Append rest of first list. */
	if (result == NULL)
	
	{
	  
	
      
      
    
  
    
    {
      
	/* Append rest of second list */
	if (result == NULL)
	
	{
	  
	
      
      
    
  



sort_object (cJSON * const object, const cJSON_bool case_sensitive)
{
  
    
    {
      
    
  



compare_json (cJSON * a, cJSON * b, const cJSON_bool case_sensitive)
{
  
    
    {
      
	/* mismatched type. */
	return false;
    
  
    
    {
    
      
	/* numeric mismatch. */
	if ((a->valueint != b->valueint)
	    || (!compare_double (a->valuedouble, b->valuedouble)))
	
	{
	  
	
      
      else
	
	{
	  
	
    
      
	/* string mismatch. */
	if (strcmp (a->valuestring, b->valuestring) != 0)
	
	{
	  
	
      
      else
	
	{
	  
	
    
      
	      (a != NULL) && (b != NULL); 
	
	{
	  
	  
	    
	    {
	      
	    
	
      
	/* array size mismatch? (one of both children is not NULL) */
	if ((a != NULL) || (b != NULL))
	
	{
	  
	
      
      else
	
	{
	  
	
    
      
      
      
	      (a != NULL) && (b != NULL); 
	
	{
	  
	  
	    /* compare object keys */
	    if (compare_strings
		((unsigned char *) a->string, (unsigned char *) b->string,
		 
	    
	    {
	      
		/* missing member */
		return false;
	    
	  
	  
	    
	    {
	      
	    
	
      
	/* object length mismatch (one of both children is not null) */
	if ((a != NULL) || (b != NULL))
	
	{
	  
	
      
      else
	
	{
	  
	
    
      
    
  
    /* null, true or false */
    return true;



/* non broken version of cJSON_InsertItemInArray */
static cJSON_bool
insert_item_in_array (cJSON * array, size_t which, cJSON * newitem)
{
  
  
    
    {
      
      
    
  
    
    {
      
	/* item is after the end of the array */
	return 0;
    
  
    
    {
      
      
    
  
    /* insert into the linked list */
    newitem->next = child;
  
  
  
    /* was it at the beginning */
    if (child == array->child)
    
    {
      
    
  
  else
    
    {
      
    
  



get_object_item (const cJSON * const object, const char *name,
		 
{
  
    
    {
      
    
  



{ INVALID, ADD, REMOVE, REPLACE, MOVE, COPY, TEST };

decode_patch_operation (const cJSON * const patch,
			
{
  
  
    
    {
      
    
  
    
    {
      
    
  
    
    {
      
    
  
    
    {
      
    
  
    
    {
      
    
  
    
    {
      
    
  
    
    {
      
    
  



/* overwrite and existing item with another one and free resources on the way */
  static void
overwrite_item (cJSON * const root, const cJSON replacement)
{
  
    
    {
      
    
  
    
    {
      
    
  
    
    {
      
    
  
    
    {
      
    
  



apply_patch (cJSON * object, const cJSON * patch,
	     
{
  
  
  
  
  
  
  
  
  
    
    {
      
	/* malformed patch. */
	status = 2;
      
    
  
  
    
    {
      
      
    
  
  else if (opcode == TEST)
    
    {
      
	/* compare value: {...} with the given path */
	status = 
				 (object, path->valuestring, case_sensitive),
				 
						     
				 
      
    
  
    /* special case for replacing the root */
    if (path->valuestring[0] == '\0')
    
    {
      
	
	{
	  
	    { NULL, NULL, NULL, cJSON_Invalid, NULL, 0, 0, NULL };
	  
	  
	  
	
      
	
	{
	  
	  
	    
	    {
	      
		/* missing "value" for add/replace. */
		status = 7;
	      
	    
	  
	  
	    
	    {
	      
		/* out of memory for add/replace. */
		status = 8;
	      
	    
	  
	  
	    /* delete the duplicated value */
	    cJSON_free (value);
	  
	  
	    /* the string "value" isn't needed */
	    if (object->string != NULL)
	    
	    {
	      
	      
	    
	  
	  
	
    
  
    
    {
      
	/* Get rid of old. */
	cJSON * old_item =
	
			
      
	
	{
	  
	  
	
      
      
	
	{
	  
	    /* For Remove, this job is done. */
	    status = 0;
	  
	
    
  
    /* Copy/Move uses "from". */
    if ((opcode == MOVE) || (opcode == COPY))
    
    {
      
      
	
	{
	  
	    /* missing "from" for copy/move. */
	    status = 4;
	  
	
      
	
	{
	  
	    
			    
	
      
	
	{
	  
	    
				      
	
      
	
	{
	  
	    /* missing "from" for copy/move. */
	    status = 5;
	  
	
      
	
	{
	  
	
      
	
	{
	  
	    /* out of memory for copy/move. */
	    status = 6;
	  
	
    
  
  else
    /* Add/Replace uses "value". */
    {
      
      
	
	{
	  
	    /* missing "value" for add/replace. */
	    status = 7;
	  
	
      
      
	
	{
	  
	    /* out of memory for add/replace. */
	    status = 8;
	  
	
    
  
    /* Now, just add "value" to "path". */
    /* split pointer in parent and child */
    parent_pointer = cJSONUtils_strdup ((unsigned char *) path->valuestring);
  
  
    
    {
      
      
    
  
    
			      case_sensitive);
  
  
    /* add, remove, replace, move, copy, test. */
    if ((parent == NULL) || (child_pointer == NULL))
    
    {
      
	/* Couldn't find object to add to. */
	status = 9;
      
    
  
  else if (cJSON_IsArray (parent))
    
    {
      
	
	{
	  
	  
	
      
      else
	
	{
	  
	  
	    
	    {
	      
	      
	    
	  
	    
	    {
	      
	      
	    
	  
	
    
  
  else if (cJSON_IsObject (parent))
    
    {
      
	
	{
	  
						      (char *) child_pointer);
	
      
      else
	
	{
	  
	
      
    
  
  else
    /* parent is not an object */
    {
      
	/* Couldn't find object to add to. */
	status = 9;
      
    

    
    {
      
    
  
    
    {
      
    
  



						  
						  const patches)
{
  
  
  
    
    {
      
	/* malformed patches. */
	return 1;
    
  
    
    {
      
    
  
    
    {
      
      
	
	{
	  
	
      
    
  



							       
							       object,
							       
							       cJSON
							       * 
							       patches)
{
  
  
  
    
    {
      
	/* malformed patches. */
	return 1;
    
  
    
    {
      
    
  
    
    {
      
      
	
	{
	  
	
      
    
  



compose_patch (cJSON * const patches, const unsigned char *const operation,
	       
	       
{
  
  
    
    {
      
    
  
  
    
    {
      
    
  
			    
  
    
    {
      
				
    
  
  else
    
    {
      
      
      
	(unsigned char *) cJSON_malloc (path_length + suffix_length +
					
      
      
      
				 
							
      
  
    
    {
      
    
  



cJSONUtils_AddPatchToArray (cJSON * const array, const char *const operation,
			    
			    
{
  
		    (const unsigned char *) path, NULL, value);


create_patches (cJSON * const patches, const unsigned char *const path,
		
		
{
  
    
    {
      
    
  
    
    {
      
			
      
    
  
    
    {
    
      
	     || !compare_double (from->valuedouble, to->valuedouble))
	
	{
	  
			    
	
      
    
      
	
	{
	  
			    
	
      
    
      
      {
	
	
	
	
	
	  /* generate patches for all array elements that exist in both "from" and "to" */
	  for (index = 0; (from_child != NULL) && (to_child != NULL);
	       (void) (from_child = from_child->next), (void) (to_child =
							       
							       
	       
	  
	  {
	    
	      /* check if conversion to unsigned long is valid
	       * This should be eliminated at compile time by dead code elimination
	       * if size_t is an alias of unsigned long, or if it is bigger */
	      if (index > ULONG_MAX)
	      
	      {
		
		
	      
	    
	    
			       
	  
	  /* remove leftover elements from 'from' that are not in 'to' */
	  for (; (from_child != NULL); (void) (from_child = from_child->next))
	  
	  {
	    
	      /* check if conversion to unsigned long is valid
	       * This should be eliminated at compile time by dead code elimination
	       * if size_t is an alias of unsigned long, or if it is bigger */
	      if (index > ULONG_MAX)
	      
	      {
		
		
	      
	    
	    
			      path, 
	  
	/* add new elements in 'to' that were not in 'from' */
	for (; (to_child != NULL);
	     (void) (to_child = to_child->next), index++)
	  
	  {
	    
			      (const unsigned char *) "-", to_child);
	  
	
      
    
      
      {
	
	
	
	
	
	
	
	  /* for all object values in the object with more of them */
	  while ((from_child != NULL) || (to_child != NULL))
	  
	  {
	    
	    
	      
	      {
		
	      
	    
	    else if (to_child == NULL)
	      
	      {
		
	      
	    
	    else
	      
	      {
		
		  
				      
				      
	    
	      
	      {
		
		  /* both object keys are the same */
		  size_t path_length = strlen ((const char *) path);
		
		  
					     
		
		  
						     
						     
		
		
					     (unsigned char *)
					     
		
		  /* create a patch for the element */
		  create_patches (patches, new_path, from_child, to_child,
				  
		
		
		
	      
	    
	    else if (diff < 0)
	      
	      {
		
		  /* object element doesn't exist in 'to' --> remove it */
		  compose_patch (patches, (const unsigned char *) "remove",
				 
				 
				 
		
	      
	    
	    else
	      
	      {
		
		  /* object element doesn't exist in 'from' --> add it */
		  compose_patch (patches, (const unsigned char *) "add", path,
				 
				 
		
	  
      
    
      
    



							 
{
  
  
    
    {
      
    
  
  
  



								      *
								      
								      
								      
								      *
								      
								      
{
  
  
    
    {
      
    
  
  
  



{
  


cJSONUtils_SortObjectCaseSensitive (cJSON * const object)
{
  


merge_patch (cJSON * target, const cJSON * const patch,
	     
{
  
  
    
    {
      
	/* scalar value, array or NULL, just duplicate */
	cJSON_Delete (target);
      
    
  
    
    {
      
      
    
  
  
    
    {
      
	
	{
	  
	    /* NULL is the indicator to remove a value, see RFC7396 */
	    if (case_sensitive)
	    
	    {
	      
							  
							  string);
	    
	  
	  else
	    
	    {
	      
	    
	
      
      else
	
	{
	  
	  
	  
	    
	    {
	      
		
							    
							    
	    
	  
	  else
	    
	    {
	      
		
	    
	  
	    
	  
	    
	    {
	      
	    
	  
				     replacement);
	
      
    
  



						    
						    const patch)
{
  



								 
								 
								 
								 
								 patch)
{
  



generate_merge_patch (cJSON * const from, cJSON * const to,
		      
{
  
  
  
  
    
    {
      
	/* patch to delete everything */
	return cJSON_CreateNull ();
    
  
    
    {
      
    
  
  
  
  
  
  
    
    {
      
      
	
	{
	  
	    
	    {
	      
	    
	  
	  else
	    
	    {
	      
	    
	
      
      else
	
	{
	  
	
      
	
	{
	  
	    /* from has a value that to doesn't have -> remove */
	    cJSON_AddItemToObject (patch, from_child->string,
				   
	  
	
      
      else if (diff > 0)
	
	{
	  
	    /* to has a value that from doesn't have -> add to patch */
	    cJSON_AddItemToObject (patch, to_child->string,
				   
	  
	
      
      else
	
	{
	  
	    /* object key exists in both objects */
	    if (!compare_json (from_child, to_child, case_sensitive))
	    
	    {
	      
		/* not identical --> generate a patch */
		cJSON_AddItemToObject (patch, to_child->string,
				       
				       (from_child, to_child));
	    
	  
	    /* next key in the object */
	    from_child = from_child->next;
	  
	
    
  
    
    {
      
	/* no patch generated */
	cJSON_Delete (patch);
      
    
  



							    
							    
							    const to)
{
  



cJSONUtils_GenerateMergePatchCaseSensitive (cJSON 
					    
{
  

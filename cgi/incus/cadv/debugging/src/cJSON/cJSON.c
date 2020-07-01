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

/* cJSON */
/* JSON parser in C. */

/* disable warnings about old C89 functions in MSVC */
#if !defined(_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER)
#define _CRT_SECURE_NO_DEPRECATE
#endif /* 

#ifdef __GNUC__
#pragma GCC visibility push(default)
#endif /* 
#if defined(_MSC_VER)
#pragma warning (push)
/* disable warning about single line comments in system headers */
#pragma warning (disable : 4001)
#endif /* 

#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <float.h>

#ifdef ENABLE_LOCALES
#include <locale.h>
#endif /* 

#if defined(_MSC_VER)
#pragma warning (pop)
#endif /* 
#ifdef __GNUC__
#pragma GCC visibility pop
#endif /* 

#include "cJSON.h"

/* define our own boolean type */
#ifdef true
#undef true
#endif /* 
#define true ((cJSON_bool)1)

#ifdef false
#undef false
#endif /* 
#define false ((cJSON_bool)0)

/* define isnan and isinf for ANSI C, if in C99 or above, isnan and isinf has been defined in math.h */
#ifndef isinf
#define isinf(d) (isnan((d - d)) && !isnan(d))
#endif /* 
#ifndef isnan
#define isnan(d) (d != d)
#endif /* 

#ifndef NAN
#define NAN 0.0/0.0
#endif /* 

{
  
  




cJSON_GetErrorPtr (void)
{
  


cJSON_GetStringValue (cJSON * item)
{
  
    
    {
      
    
  



{
  
    
    {
      
    
  



/* This is a safeguard to prevent copy-pasters from using incompatible C and header files */
#if (CJSON_VERSION_MAJOR != 1) || (CJSON_VERSION_MINOR != 7) || (CJSON_VERSION_PATCH != 13)
#error cJSON.h and cJSON.c have different versions. Make sure that both have the same.
#endif /* 
  
{
  
  
	      
  



/* Case insensitive string comparison, doesn't consider two NULL pointers equal though */
  static int
case_insensitive_strcmp (const unsigned char *string1,
			 
{
  
    
    {
      
    
  
    
    {
      
    
  
	   (void) string1++, string2++)
    
    {
      
	
	{
	  
	
    
  



{
  
  
  


#if defined(_MSC_VER)
/* work around MSVC error C2322: '...' address of dllimport '...' is not static */
static void *CJSON_CDECL
internal_malloc (size_t size)
{
  



internal_free (void *pointer)
{
  


internal_realloc (void *pointer, size_t size)
{
  



#else /* 
#define internal_malloc malloc
#define internal_free free
#define internal_realloc realloc
#endif /* 
/* strlen of character literals resolved at compile time */
#define static_strlen(string_literal) (sizeof(string_literal) - sizeof(""))

  { internal_malloc, internal_free, internal_realloc };

cJSON_strdup (const unsigned char *string, const internal_hooks * const hooks)
{
  
  
  
    
    {
      
    
  
  
  
    
    {
      
    
  
  



{
  
    
    {
      
	/* Reset hooks */
	global_hooks.allocate = malloc;
      
      
      
    
  
  
    
    {
      
    
  
  
    
    {
      
    
  
    /* use realloc only if both free and malloc are used */
    global_hooks.reallocate = NULL;
  
	 && (global_hooks.deallocate == free))
    
    {
      
    



/* Internal constructor. */
static cJSON *
cJSON_New_Item (const internal_hooks * const hooks)
{
  
  
    
    {
      
    
  



/* Delete a cJSON structure. */
  CJSON_PUBLIC (void) cJSON_Delete (cJSON * item)
{
  
  
    
    {
      
      
	
	{
	  
	
      
	
	{
	  
	
      
	
	{
	  
	
      
      
    



/* get the decimal point character of the current locale */
  static unsigned char
get_decimal_point (void)
{
  
#ifdef ENABLE_LOCALES
  struct lconv *lconv = localeconv ();
  
  
#else /* 
    return '.';
  
#endif /* 
}


{
  
  
  
  
  


/* check if the given size is left to read in a given parse buffer (starting with 1) */
#define can_read(buffer, size) ((buffer != NULL) && (((buffer)->offset + size) <= (buffer)->length))
/* check if the buffer can be accessed at the given index (starting with 0) */
#define can_access_at_index(buffer, index) ((buffer != NULL) && (((buffer)->offset + index) < (buffer)->length))
#define cannot_access_at_index(buffer, index) (!can_access_at_index(buffer, index))
/* get a pointer to the buffer at the position */
#define buffer_at_offset(buffer) ((buffer)->content + (buffer)->offset)
/* Parse the input text to generate a number, and populate the result into item. */
static cJSON_bool
parse_number (cJSON * const item, parse_buffer * const input_buffer)
{
  
  
  
  
  
  
    
    {
      
    
  
    /* copy the number into a temporary buffer and replace '.' with the decimal point
     * of the current locale (for strtod)
     * This also takes care of '\0' not necessarily being available for marking the end of the input */
    for (i = 0;
	 (i < (sizeof (number_c_string) - 1))
	 && can_access_at_index (input_buffer, i); i++)
    
    {
      
	
	{
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	  
	  
	
	  
	  
	
	  
	
    

  
  
    
    {
      
    
  
  
    /* use saturation in case of overflow */
    if (number >= INT_MAX)
    
    {
      
    
  
  else if (number <= (double) INT_MIN)
    
    {
      
    
  
  else
    
    {
      
    
  
  



/* don't ask me, but the original cJSON_SetNumberValue returns an integer or double */
  CJSON_PUBLIC (double) cJSON_SetNumberHelper (cJSON * object, double number)
{
  
    
    {
      
    
  
  else if (number <= (double) INT_MIN)
    
    {
      
    
  
  else
    
    {
      
    



						  
{
  
  
    /* if object's type is not cJSON_String or is cJSON_IsReference, it should not set valuestring */
    if (!(object->type & cJSON_String) || (object->type & cJSON_IsReference))
    
    {
      
    
  
    
    {
      
      
    
  
    (char *) cJSON_strdup ((const unsigned char *) valuestring,
			   
  
    
    {
      
    
  
    
    {
      
    
  
  



{
  
  
  
  
  
  
  


/* realloc printbuffer if necessary to have at least "needed" bytes more */
static unsigned char *
ensure (printbuffer * const p, size_t needed)
{
  
  
  
    
    {
      
    
  
    
    {
      
	/* make sure that offset is valid */
	return NULL;
    
  
    
    {
      
	/* sizes bigger than INT_MAX are currently not supported */
	return NULL;
    
  
  
    
    {
      
    
  
    
    {
      
    
  
    /* calculate new buffer size */
    if (needed > (INT_MAX / 2))
    
    {
      
	/* overflow of int, use INT_MAX if possible */
	if (needed <= INT_MAX)
	
	{
	  
	
      
      else
	
	{
	  
	
    
  
  else
    
    {
      
    
  
    
    {
      
	/* reallocate with realloc if available */
	newbuffer =
	(unsigned char *) p->hooks.reallocate (p->buffer, newsize);
      
	
	{
	  
	  
	  
	  
	
    
  
  else
    
    {
      
	/* otherwise reallocate manually */
	newbuffer = (unsigned char *) p->hooks.allocate (newsize);
      
	
	{
	  
	  
	  
	  
	
      
	
	{
	  
	
      
    
  
  
  



/* calculate the new length of the string in a printbuffer and update the offset */
  static void
update_offset (printbuffer * const buffer)
{
  
  
    
    {
      
    
  
  


/* securely comparison of floating-point variables */
static cJSON_bool
compare_double (double a, double b)
{
  
  



/* Render the number nicely from the given item into a string. */
static cJSON_bool
print_number (const cJSON * const item, printbuffer * const output_buffer)
{
  
  
  
  
  
  
  
  
    
    {
      
    
  
    /* This checks for NaN and Infinity */
    if (isnan (d) || isinf (d))
    
    {
      
    
  
  else
    
    {
      
	/* Try 15 decimal places of precision to avoid nonsignificant nonzero digits */
	length = sprintf ((char *) number_buffer, "%1.15g", d);
      
	/* Check whether the original double can be recovered */
	if ((sscanf ((char *) number_buffer, "%lg", &test) != 1)
	    || !compare_double ((double) test, d))
	
	{
	  
	    /* If not, print with 17 decimal places of precision */
	    length = sprintf ((char *) number_buffer, "%1.17g", d);
	
    
    /* sprintf failed or buffer overrun occurred */
    if ((length < 0) || (length > (int) (sizeof (number_buffer) - 1)))
    
    {
      
    
  
    /* reserve appropriate space in the output */
    output_pointer = ensure (output_buffer, (size_t) length + sizeof (""));
  
    
    {
      
    
  
    /* copy the printed number to the output and replace locale
     * dependent decimal point with '.' */
    for (i = 0; i < ((size_t) length); i++)
    
    {
      
	
	{
	  
	  
	
      
    
  
  
  



/* parse 4 digit hexadecimal number */
  static unsigned
parse_hex4 (const unsigned char *const input)
{
  
  
  
    
    {
      
	/* parse digit */
	if ((input[i] >= '0') && (input[i] <= '9'))
	
	{
	  
	
      
      else if ((input[i] >= 'A') && (input[i] <= 'F'))
	
	{
	  
	
      
      else if ((input[i] >= 'a') && (input[i] <= 'f'))
	
	{
	  
	
      
      else
	/* invalid */
	{
	  
	
      
	
	{
	  
	    /* shift left to make place for the next nibble */
	    h = h << 4;
	
    
  



/* converts a UTF-16 literal to UTF-8
 * A literal can be one or two sequences of the form \uXXXX */
  static unsigned char
utf16_literal_to_utf8 (const unsigned char *const input_pointer,
		       
		       
{
  
  
  
  
  
  
  
  
    
    {
      
	/* input ends unexpectedly */
	goto fail;
    
  
    /* get the first utf16 sequence */
    first_code = parse_hex4 (first_sequence + 2);
  
    /* check that the code is valid */
    if (((first_code >= 0xDC00) && (first_code <= 0xDFFF)))
    
    {
      
    
  
    /* UTF16 surrogate pair */
    if ((first_code >= 0xD800) && (first_code <= 0xDBFF))
    
    {
      
      
      
      
	
	{
	  
	    /* input ends unexpectedly */
	    goto fail;
	
      
	
	{
	  
	    /* missing second half of the surrogate pair */
	    goto fail;
	
      
	/* get the second utf16 sequence */
	second_code = parse_hex4 (second_sequence + 2);
      
	/* check that the code is valid */
	if ((second_code < 0xDC00) || (second_code > 0xDFFF))
	
	{
	  
	    /* invalid second half of the surrogate pair */
	    goto fail;
	
      
	/* calculate the unicode codepoint from the surrogate pair */
	codepoint =
	
    
  
  else
    
    {
      
      
    
  
    /* encode as UTF-8
     * takes at maximum 4 bytes to encode:
     * 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx */
    if (codepoint < 0x80)
    
    {
      
	/* normal ascii, encoding 0xxxxxxx */
	utf8_length = 1;
    
  
  else if (codepoint < 0x800)
    
    {
      
	/* two bytes, encoding 110xxxxx 10xxxxxx */
	utf8_length = 2;
      
    
  
  else if (codepoint < 0x10000)
    
    {
      
	/* three bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx */
	utf8_length = 3;
      
    
  
  else if (codepoint <= 0x10FFFF)
    
    {
      
	/* four bytes, encoding 1110xxxx 10xxxxxx 10xxxxxx 10xxxxxx */
	utf8_length = 4;
      
    
  
  else
    
    {
      
	/* invalid unicode codepoint */
	goto fail;
    
  
    /* encode as utf8 */
    for (utf8_position = (unsigned char) (utf8_length - 1); utf8_position > 0;
	 
    
    {
      
	/* 10xxxxxx */
	(*output_pointer)[utf8_position] =
	(unsigned char) ((codepoint | 0x80) & 0xBF);
      
    
  /* encode first byte */
  if (utf8_length > 1)
    
    {
      
	(unsigned char) ((codepoint | first_byte_mark) & 0xFF);
    
  
  else
    
    {
      
    
  




/* Parse the input text into an unescaped cinput, and populate item. */
static cJSON_bool
parse_string (cJSON * const item, parse_buffer * const input_buffer)
{
  
  
  
  
  
    /* not a string */
    if (buffer_at_offset (input_buffer)[0] != '\"')
    
    {
      
    
  
  {
    
      /* calculate approximate size of the output (overestimate) */
      size_t allocation_length = 0;
    
    
	       
      
      {
	
	  /* is escape sequence */
	  if (input_end[0] == '\\')
	  
	  {
	    
		   
	      
	      {
		
		  /* prevent buffer overflow when last input character is a backslash */
		  goto fail;
	      
	    
	    
	  
	
      
    
	    
      
      {
	
      
    
      /* This is at most how much we need for the output */
      allocation_length =
      (size_t) (input_end - buffer_at_offset (input_buffer)) - skipped_bytes;
    
      (unsigned char *) input_buffer->hooks.allocate (allocation_length +
						      
    
      
      {
	
      
  
  
  
    /* loop through the string literal */
    while (input_pointer < input_end)
    
    {
      
	
	{
	  
	
      
	/* escape sequence */
	else
	
	{
	  
	  
	    
	    {
	      
	    
	  
	    
	    {
	    
	      
	      
	    
	      
	      
	    
	      
	      
	    
	      
	      
	    
	      
	      
	    
	    
	    
	      
	      
	      
		/* UTF-16 literal */
	    case 'u':
	      
		
					  
	      
		
		{
		  
		    /* failed to convert UTF16-literal to UTF-8 */
		    goto fail;
		
	      
	    
	      
	    
	  
	
    
  
    /* zero terminate the output */
    *output_pointer = '\0';
  
  
  
  
  

    
    {
      
    
  
    
    {
      
	(size_t) (input_pointer - input_buffer->content);
    
  



/* Render the cstring provided to an escaped version that can be printed. */
static cJSON_bool
print_string_ptr (const unsigned char *const input,
		  
{
  
  
  
  
  
    /* numbers of additional characters needed for escaping */
    size_t escape_characters = 0;
  
    
    {
      
    
  
    /* empty string */
    if (input == NULL)
    
    {
      
      
	
	{
	  
	
      
      
    
  
    /* set "flag" to 1 if something needs to be escaped */
    for (input_pointer = input; *input_pointer; input_pointer++)
    
    {
      
	
	{
	
	
	
	
	
	
	
	  
	    /* one character escape sequence */
	    escape_characters++;
	  
	
	  
	    
	    {
	      
		/* UTF-16 escape sequence uXXXX */
		escape_characters += 5;
	    
	  
	
    
  
  
  
    
    {
      
    
  
    /* no characters have to be escaped */
    if (escape_characters == 0)
    
    {
      
      
      
      
      
    
  
  
  
    /* copy the string */
    for (input_pointer = input; *input_pointer != '\0';
	 (void) input_pointer++, output_pointer++)
    
    {
      
	     && (*input_pointer != '\\'))
	
	{
	  
	    /* normal character, copy */
	    *output_pointer = *input_pointer;
	
      
      else
	
	{
	  
	    /* character needs to be escaped */
	    *output_pointer++ = '\\';
	  
	    
	    {
	    
	      
	      
	    
	      
	      
	    
	      
	      
	    
	      
	      
	    
	      
	      
	    
	      
	      
	    
	      
	      
	    
	      
		/* escape and print as unicode codepoint */
		sprintf ((char *) output_pointer, "u%04x", *input_pointer);
	      
	      
	    
	
    
  
  
  



/* Invoke print_string_ptr (which is useful) on an item. */
static cJSON_bool
print_string (const cJSON * const item, printbuffer * const p)
{
  


/* Predeclare these prototypes. */
static cJSON_bool parse_value (cJSON * const item,
			       

				  

				  

				  

				   

				   

/* Utility to jump whitespace and cr/lf */
static parse_buffer *
buffer_skip_whitespace (parse_buffer * const buffer)
{
  
    
    {
      
    
  
    
    {
      
    
  
	     && (buffer_at_offset (buffer)[0] <= 32))
    
    {
      
    
  
    
    {
      
    
  



/* skip the UTF-8 BOM (byte order mark) if it is at the beginning of a buffer */
static parse_buffer *
skip_utf8_bom (parse_buffer * const buffer)
{
  
	 || (buffer->offset != 0))
    
    {
      
    
  
	  &&
	  (strncmp
	   ((const char *) buffer_at_offset (buffer), "\xEF\xBB\xBF",
	    
    
    {
      
    
  



						  
						  
						  
						  require_null_terminated)
{
  
  
    
    {
      
    
  
    /* Adding null character size due to require_null_terminated. */
    buffer_length = strlen (value) + sizeof ("");
  
					
					



/* Parse an object - create a new root, and populate. */
  CJSON_PUBLIC (cJSON *) cJSON_ParseWithLengthOpts (const char *value,
						    
						    
						    
						    
						    require_null_terminated)
{
  
  {
    
    {
  
  
  
    /* reset error position */
    global_error.json = NULL;
  
  
    
    {
      
    
  
  
  
  
  
  
    
    {
      
    
  
	  (item, buffer_skip_whitespace (skip_utf8_bom (&buffer))))
    
    {
      
	/* parse failure. ep is set. */
	goto fail;
    
  
    /* if we require null-terminated JSON without appended garbage, skip and then check for a null terminator */
    if (require_null_terminated)
    
    {
      
      
	     || buffer_at_offset (&buffer)[0] != '\0')
	
	{
	  
	
    
  
    
    {
      
    
  

    
    {
      
    
  
    
    {
      
      
      
      
	
	{
	  
	
      
      else if (buffer.length > 0)
	
	{
	  
	
      
	
	{
	  
	    (const char *) local_error.json + local_error.position;
	
      
    
  



/* Default options for cJSON_Parse */
  CJSON_PUBLIC (cJSON *) cJSON_Parse (const char *value)
{
  



						    
{
  



#define cjson_min(a, b) (((a) < (b)) ? (a) : (b))

print (const cJSON * const item, cJSON_bool format,
       
{
  
  
  
  
  
    /* create buffer */
    buffer->buffer = (unsigned char *) hooks->allocate (default_buffer_size);
  
  
  
  
    
    {
      
    
  
    /* print the value */
    if (!print_value (item, buffer))
    
    {
      
    
  
  
    /* check if reallocate is available */
    if (hooks->reallocate != NULL)
    
    {
      
	(unsigned char *) hooks->reallocate (buffer->buffer,
					     
      
	
	{
	  
	
      
    
  
  else
    /* otherwise copy the JSON over to a new buffer */
    {
      
      
	
	{
	  
	
      
		 
      
      
	/* free the buffer */
	hooks->deallocate (buffer->buffer);
    
  

    
    {
      
    
  
    
    {
      
    
  



/* Render a cJSON item/entity/structure to text. */
  CJSON_PUBLIC (char *) cJSON_Print (const cJSON * item)
{
  


cJSON_PrintUnformatted (const cJSON * item)
{
  


cJSON_PrintBuffered (const cJSON * item, int prebuffer, cJSON_bool fmt)
{
  
  {
    
    {
  
  
    
    {
      
    
  
  
    
    {
      
    
  
  
  
  
  
  
    
    {
      
      
    
  

							  
							  
							  length,
							  
							  cJSON_bool 
{
  
  {
    
    {
  
  
    
    {
      
    
  
  
  
  
  
  
  



/* Parser core - when encountering text, process appropriately. */
static cJSON_bool
parse_value (cJSON * const item, parse_buffer * const input_buffer)
{
  
    
    {
      
    
  
    /* parse the different types of values */
    /* null */
    if (can_read (input_buffer, 4)
	&&
	(strncmp ((const char *) buffer_at_offset (input_buffer), "null", 4)
	 
    
    {
      
      
      
    
  
    /* false */
    if (can_read (input_buffer, 5)
	&& (strncmp
	    ((const char *) buffer_at_offset (input_buffer), "false",
	     
    
    {
      
      
      
    
  
    /* true */
    if (can_read (input_buffer, 4)
	&&
	(strncmp ((const char *) buffer_at_offset (input_buffer), "true", 4)
	 
    
    {
      
      
      
      
    
  
    /* string */
    if (can_access_at_index (input_buffer, 0)
	&& (buffer_at_offset (input_buffer)[0] == '\"'))
    
    {
      
    
  
    /* number */
    if (can_access_at_index (input_buffer, 0)
	&& ((buffer_at_offset (input_buffer)[0] == '-')
	    || ((buffer_at_offset (input_buffer)[0] >= '0')
		&& (buffer_at_offset (input_buffer)[0] <= '9'))))
    
    {
      
    
  
    /* array */
    if (can_access_at_index (input_buffer, 0)
	&& (buffer_at_offset (input_buffer)[0] == '['))
    
    {
      
    
  
    /* object */
    if (can_access_at_index (input_buffer, 0)
	&& (buffer_at_offset (input_buffer)[0] == '{'))
    
    {
      
    
  



/* Render a value to text. */
static cJSON_bool
print_value (const cJSON * const item, printbuffer * const output_buffer)
{
  
  
    
    {
      
    
  
    
    {
    
      
      
	
	{
	  
	
      
      
    
      
      
	
	{
	  
	
      
      
    
      
      
	
	{
	  
	
      
      
    
      
    
      
      {
	
	
	  
	  {
	    
	  
	
	
	
	  
	  {
	    
	  
	
	
      
    
      
    
      
    
      
    
      
    



/* Build an array from input text. */
static cJSON_bool
parse_array (cJSON * const item, parse_buffer * const input_buffer)
{
  
  
  
    
    {
      
    
  
  
    
    {
      
	/* not an array */
	goto fail;
    
  
  
  
	 && (buffer_at_offset (input_buffer)[0] == ']'))
    
    {
      
	/* empty array */
	goto success;
    
  
    /* check if we skipped to the end of the buffer */
    if (cannot_access_at_index (input_buffer, 0))
    
    {
      
      
    
  
    /* step back to character in front of the first element */
    input_buffer->offset--;
  
    /* loop through the comma separated array elements */
    do
    
    {
      
	/* allocate next item */
	cJSON * new_item = cJSON_New_Item (&(input_buffer->hooks));
      
	
	{
	  
	
      
	/* attach next item to list */
	if (head == NULL)
	
	{
	  
	    /* start the linked list */
	    current_item = head = new_item;
	
      
      else
	
	{
	  
	    /* add to the end and advance */
	    current_item->next = new_item;
	  
	  
	
      
	/* parse next value */
	input_buffer->offset++;
      
      
	
	{
	  
	
      
    
  
	    && (buffer_at_offset (input_buffer)[0] == ','));
  
	  || buffer_at_offset (input_buffer)[0] != ']')
    
    {
      
    

  
  
  
  

    
    {
      
    
  



/* Render an array to text */
static cJSON_bool
print_array (const cJSON * const item, printbuffer * const output_buffer)
{
  
  
  
  
    
    {
      
    
  
    /* Compose the output array. */
    /* opening square bracket */
    output_pointer = ensure (output_buffer, 1);
  
    
    {
      
    
  
  
  
  
    
    {
      
	
	{
	  
	
      
      
	
	{
	  
	  
	  
	    
	    {
	      
	    
	  
	  
	    
	    {
	      
	    
	  
	  
	
      
    
  
  
    
    {
      
    
  
  
  
  



/* Build an object from the text. */
static cJSON_bool
parse_object (cJSON * const item, parse_buffer * const input_buffer)
{
  
  
  
    
    {
      
    
  
  
	  || (buffer_at_offset (input_buffer)[0] != '{'))
    
    {
      
    
  
  
  
	 && (buffer_at_offset (input_buffer)[0] == '}'))
    
    {
      
    
  
    /* check if we skipped to the end of the buffer */
    if (cannot_access_at_index (input_buffer, 0))
    
    {
      
      
    
  
    /* step back to character in front of the first element */
    input_buffer->offset--;
  
    /* loop through the comma separated array elements */
    do
    
    {
      
	/* allocate next item */
	cJSON * new_item = cJSON_New_Item (&(input_buffer->hooks));
      
	
	{
	  
	
      
	/* attach next item to list */
	if (head == NULL)
	
	{
	  
	    /* start the linked list */
	    current_item = head = new_item;
	
      
      else
	
	{
	  
	    /* add to the end and advance */
	    current_item->next = new_item;
	  
	  
	
      
	/* parse the name of the child */
	input_buffer->offset++;
      
      
	
	{
	  
	
      
      
	/* swap valuestring and string, because we parsed the name */
	current_item->string = current_item->valuestring;
      
      
	      || (buffer_at_offset (input_buffer)[0] != ':'))
	
	{
	  
	
      
	/* parse the value */
	input_buffer->offset++;
      
      
	
	{
	  
	
      
    
  
	    && (buffer_at_offset (input_buffer)[0] == ','));
  
	  || (buffer_at_offset (input_buffer)[0] != '}'))
    
    {
      
    

  
  
  
  

    
    {
      
    
  



/* Render an object to text. */
static cJSON_bool
print_object (const cJSON * const item, printbuffer * const output_buffer)
{
  
  
  
  
    
    {
      
    
  
    /* Compose the output: */
    length = (size_t) (output_buffer->format ? 2 : 1);	/* fmt: {\n */
  
  
    
    {
      
    
  
  
  
    
    {
      
    
  
  
    
    {
      
	
	{
	  
	  
	  
	    
	    {
	      
	    
	  
	    
	    {
	      
	    
	  
	
      
	/* print key */
	if (!print_string_ptr
	    ((unsigned char *) current_item->string, output_buffer))
	
	{
	  
	
      
      
      
      
	
	{
	  
	
      
      
	
	{
	  
	
      
      
	/* print value */
	if (!print_value (current_item, output_buffer))
	
	{
	  
	
      
      
	/* print comma if not last */
	length =
	((size_t) (output_buffer->format ? 1 : 0) +
	 (size_t) (current_item->next ? 1 : 0));
      
      
	
	{
	  
	
      
	
	{
	  
	
      
	
	{
	  
	
      
      
      
    
  
    
	       
  
    
    {
      
    
  
    
    {
      
      
	
	{
	  
	
    
  
  
  
  



/* Get Array size/item / object item. */
  CJSON_PUBLIC (int) cJSON_GetArraySize (const cJSON * array)
{
  
  
  
    
    {
      
    
  
  
    
    {
      
      
    
  
    /* FIXME: Can overflow here. Cannot be fixed without breaking the API */
    


get_array_item (const cJSON * array, size_t index)
{
  
  
    
    {
      
    
  
  
    
    {
      
      
    
  



						 int index)
{
  
    
    {
      
    
  



get_object_item (const cJSON * const object, const char *const name,
		 
{
  
  
    
    {
      
    
  
  
    
    {
      
		&& (current_element->string !=
		    
	
	{
	  
	
    
  
  else
    
    {
      
		&&
		(case_insensitive_strcmp
		 ((const unsigned char *) name,
		  (const unsigned char *) (current_element->string)) != 0))
	
	{
	  
  
		  || (current_element->string == NULL))
    
    {
      
    
  



						  const object,
						  
{
  



							       
							       
							       
							       char 
							       
{
  



						     
{
  



/* Utility for array list handling. */
  static void
suffix_object (cJSON * prev, cJSON * item)
{
  
  


/* Utility for handling references. */
static cJSON *
create_reference (const cJSON * item, const internal_hooks * const hooks)
{
  
  
    
    {
      
    
  
  
    
    {
      
    
  
  
  
  
  



add_item_to_array (cJSON * array, cJSON * item)
{
  
  
    
    {
      
    
  
  
    /*
     * To find the last item in array quickly, we use prev in array
     */
    if (child == NULL)
    
    {
      
	/* list is empty, start new one */
	array->child = item;
      
      
    
  
  else
    
    {
      
	/* append to the end */
	if (child->prev)
	
	{
	  
	  
	
      
      else
	
	{
	  
	    
	    {
	      
	    
	  
	  
	
    
  



/* Add item to array/object. */
  CJSON_PUBLIC (cJSON_bool) cJSON_AddItemToArray (cJSON * array, cJSON * item)
{
  



#if defined(__clang__) || (defined(__GNUC__)  && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ > 5))))
#pragma GCC diagnostic push
#endif /* 
#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wcast-qual"
#endif /* 
/* helper function to cast away const */
static void *
cast_away_const (const void *string)
{
  


#if defined(__clang__) || (defined(__GNUC__)  && ((__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ > 5))))
#pragma GCC diagnostic pop
#endif /* 

add_item_to_object (cJSON * const object, const char *const string,
		    
		    const internal_hooks * const hooks,
		    
{
  
  
  
	  || (object == item))
    
    {
      
    
  
    
    {
      
      
    
  
  else
    
    {
      
	(char *) cJSON_strdup ((const unsigned char *) string, hooks);
      
	
	{
	  
	
      
    
  
    
    {
      
    
  
  
  



						       
						       *string,
						       
{
  



/* Add an item to an object with constant string as key */
  CJSON_PUBLIC (cJSON_bool) cJSON_AddItemToObjectCS (cJSON * object,
						     
						     
{
  



							       array,
							       
							       item)
{
  
    
    {
      
    
  
				create_reference (item, &global_hooks));



								
								
								char
								
								
								item)
{
  
    
    {
      
    
  
				 
				 



						    
{
  
  
    
    {
      
    
  
  



						    
{
  
  
    
    {
      
    
  
  



						     
						     name)
{
  
  
    
    {
      
    
  
  



						    
						    name,
						    
						    boolean)
{
  
  
    
    {
      
    
  
  



						      
						      
						      
{
  
  
    
    {
      
    
  
  



						      
						      
						      
						      
{
  
  
    
    {
      
    
  
  



						   
						   name,
						   
{
  
  
    
    {
      
    
  
  



						      
						      name)
{
  
  
    
    {
      
    
  
  



						     
						     name)
{
  
  
    
    {
      
    
  
  



							 
							 const item)
{
  
    
    {
      
    
  
    
    {
      
	/* not the first element */
	item->prev->next = item->next;
    
  
    
    {
      
	/* not the last element */
	item->next->prev = item->prev;
    
  
    
    {
      
	/* first element */
	parent->child = item->next;
    
  
    /* make sure the detached item doesn't point anywhere anymore */
    item->prev = NULL;
  
  



							
{
  
    
    {
      
    
  
								  (size_t)
								  which));



{
  

							  
							  *string)
{
  
  



								      *
								      
								      
								      
								      
{
  
  



						      
{
  


cJSON_DeleteItemFromObjectCaseSensitive (cJSON * object, const char *string)
{
  


/* Replace array/object items with new ones. */
  CJSON_PUBLIC (cJSON_bool) cJSON_InsertItemInArray (cJSON * array, int which,
						     
{
  
  
    
    {
      
    
  
  
    
    {
      
    
  
  
  
  
    
    {
      
    
  
  else
    
    {
      
    
  



							     
							     parent,
							     
							     
							     
							     
{
  
    
    {
      
    
  
    
    {
      
    
  
  
  
    
    {
      
    
  
    
    {
      
    
  
  else
    
    {				/*
				 * To find the last item in array quickly, we use prev in array.
				 * We can't modify the last item's next pointer where this item was the parent's child
				 */
      
	
	{
	  
	
    
  
  
  
  



							  
							  
{
  
    
    {
      
    
  
								   (size_t)
								   which),
					  



replace_item_in_object (cJSON * object, const char *string,
			
{
  
    
    {
      
    
  
    /* replace the name in the replacement */
    if (!(replacement->type & cJSON_StringIsConst)
	&& (replacement->string != NULL))
    
    {
      
    
  
    (char *) cJSON_strdup ((const unsigned char *) string, &global_hooks);
  
  
					  
							      string,
							      
					  



							   
							   
							   
{
  



cJSON_ReplaceItemInObjectCaseSensitive (cJSON 
					
					
{
  



/* Create basic types: */
  CJSON_PUBLIC (cJSON *) cJSON_CreateNull (void)
{
  
  
    
    {
      
    
  



{
  
  
    
    {
      
    
  



{
  
  
    
    {
      
    
  



{
  
  
    
    {
      
    
  



{
  
  
    
    {
      
      
      
	/* use saturation in case of overflow */
	if (num >= INT_MAX)
	
	{
	  
	
      
      else if (num <= (double) INT_MIN)
	
	{
	  
	
      
      else
	
	{
	  
    
  



{
  
  
    
    {
      
      
	(char *) cJSON_strdup ((const unsigned char *) string, &global_hooks);
      
	
	{
	  
	  
	
    
  



{
  
  
    
    {
      
      
    
  



{
  
  
    
    {
      
      
    
  



{
  
  
    
    {
      
      
    
  



{
  
  
    
    {
      
      
	(char *) cJSON_strdup ((const unsigned char *) raw, &global_hooks);
      
	
	{
	  
	  
	
    
  



{
  
  
    
    {
      
    
  



{
  
  
    
    {
      
    
  



/* Create Arrays: */
  CJSON_PUBLIC (cJSON *) cJSON_CreateIntArray (const int *numbers, int count)
{
  
  
  
  
  
    
    {
      
    
  
  
    
    {
      
      
	
	{
	  
	  
	
      
	
	{
	  
	
      
      else
	
	{
	  
	
      
    
  



						     
{
  
  
  
  
  
    
    {
      
    
  
  
    
    {
      
      
	
	{
	  
	  
	
      
	
	{
	  
	
      
      else
	
	{
	  
	
      
    
  



						      
{
  
  
  
  
  
    
    {
      
    
  
  
    
    {
      
      
	
	{
	  
	  
	
      
	
	{
	  
	
      
      else
	
	{
	  
	
      
    
  



						      
{
  
  
  
  
  
    
    {
      
    
  
  
    
    {
      
      
	
	{
	  
	  
	
      
	
	{
	  
	
      
      else
	
	{
	  
	
      
    
  



/* Duplication */
  CJSON_PUBLIC (cJSON *) cJSON_Duplicate (const cJSON * item,
					  
{
  
  
  
  
  
    /* Bail on bad ptr */
    if (!item)
    
    {
      
    
  
    /* Create new item */
    newitem = cJSON_New_Item (&global_hooks);
  
    
    {
      
    
  
    /* Copy over all vars */
    newitem->type = item->type & (~cJSON_IsReference);
  
  
  
    
    {
      
	(char *) cJSON_strdup ((unsigned char *) item->valuestring,
			       
      
	
	{
	  
	
    
  
    
    {
      
	(item->
	
      
	
	{
	  
	
    
  
    /* If non-recursive, then we're done! */
    if (!recurse)
    
    {
      
    
  
    /* Walk the ->next chain for the child. */
    child = item->child;
  
    
    {
      
      
	
	{
	  
	
      
	
	{
	  
	    /* If newitem->child already set, then crosswire ->prev and ->next and move on */
	    next->next = newchild;
	  
	  
	
      
      else
	
	{
	  
	    /* Set newitem->child and move to it */
	    newitem->child = newchild;
	  
	
      
    
  

    
    {
      
    
  



skip_oneline_comment (char **input)
{
  
  
    
    {
      
	
	{
	  
	  
	
    



skip_multiline_comment (char **input)
{
  
  
    
    {
      
	
	{
	  
	  
	
    



minify_string (char **input, char **output)
{
  
  
  
  
    
    {
      
      
	
	{
	  
	  
	  
	  
	
      
      else if (((*input)[0] == '\\') && ((*input)[1] == '\"'))
	
	{
	  
	  
	  
	
    



cJSON_Minify (char *json)
{
  
  
    
    {
      
    
  
    
    {
      
	
	{
	
	
	
	
	  
	  
	
	  
	    
	    {
	      
	    
	  
	  else if (json[1] == '*')
	    
	    {
	      
	    
	  
	  else
	    
	    {
	      
	    
	  
	
	  
	  
	
	  
	  
	  
	
    
  
    /* and null-terminate. */
    *into = '\0';



{
  
    
    {
      
    
  



{
  
    
    {
      
    
  



{
  
    
    {
      
    
  



{
  
    
    {
      
    
  



{
  
    
    {
      
    
  



{
  
    
    {
      
    
  



{
  
    
    {
      
    
  



{
  
    
    {
      
    
  



{
  
    
    {
      
    
  



{
  
    
    {
      
    
  



					       
					       
					       case_sensitive)
{
  
	 || ((a->type & 0xFF) != (b->type & 0xFF)) 
    
    {
      
    
  
    /* check if type is valid */
    switch (a->type & 0xFF)
    
    {
    
    
    
    
    
    
    
    
      
    
      
    
  
    /* identical objects are equal */
    if (a == b)
    
    {
      
    
  
    
    {
      
	/* in these cases and equal type is enough */
    case cJSON_False:
    
    
      
    
      
	
	{
	  
	
      
    
    
      
	
	{
	  
	
      
	
	{
	  
	
      
    
      
      {
	
	
	
	  
	  {
	    
	      
	      {
		
	      
	    
	    
	  
	
	  /* one of the arrays is longer than the other */
	  if (a_element != b_element)
	  
	  {
	    
	  
	
      
    
      
      {
	
	
	
	{
	  
	    /* TODO This has O(n^2) runtime, which is horrible! */
	    b_element =
	    
	  
	    
	    {
	      
	    
	  
	    
	    {
	      
	    
	
	
	  /* doing this twice, once on a and b to prevent true comparison if a subset of b
	   * TODO: Do this the proper way, this is just a fix for now */
	  cJSON_ArrayForEach (b_element, b)
	{
	  
	    
	  
	    
	    {
	      
	    
	  
	    
	    {
	      
	    
	
	
      
    
      
    



{
  



{
  

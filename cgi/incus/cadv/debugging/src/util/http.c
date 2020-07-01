/*!@file a.c
 * @brief http utilities
 */
#include"util/http.h"
#include<string.h>
#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
/*! Searches URL query string for key value
 * 
 *  Given query string `input` this function attempts to
 *  find `find` key and populates `**dst`, a pointer to
 *  a pointer. Memory will be allocated to dest if found
 *  and it will be populated with the value
 *
 *  If the key was not found, `dest` is set to `NULL`
 * 
 *  Remember to free `dest` it was not found
 *
    \param dest destination buffer
    \param input input streag to search
    \param find needle to search for
 */
void
httpString (char **dest, char *input, const char *find)
{
  
  
    
    {
      
      return;
    
  
  
    
    {
      
      return;
    
  
  
  
    
    {
      
	//end_value=strchr(value,0)-1;//-1!
	end_value = strchr (value, 0);	//-1!
    }
  
  
  
    
    {
      
      return;
    
  
  
  
    //decode
  char *decoded = (char *) malloc (strlen (*dest) + 1);
  
    
    {
      
	
	{
	  
	
      
      else
	
	{
	  
	  
	
    
  
  else
    
    {
      
    



/*! Reads request body from `stdin` given
 *  \param len Number of bytes to read
 *  \param fp stream to read from
 *  \return `string` populated from stream with `len` bytes
 */

stream2buf (unsigned long len, FILE * fp)
{
  
  
  size_t brd = fread (buf, 1, len, fp);	//bytes read
  buf[brd] = '\0';		//add terminator
  /*
     //memset(buf+brd+1,(int)'\0',(len+2)-(size_t)(brd+1));       //terminator
     fprintf(stderr,"2\n");
     fprintf("brd: %zu\n",brd);
     fprintf("BUF: %s\n",buf);
   */
  return buf;



/*! Checks if a character is a hexadecimal character (ripped from rosetta)
    \param x character to check
    \return `1` if hex, else `0`
 */
  int
ishex (int x)
{
  
    (x >= 'a' && x <= 'f') || (x >= 'A' && x <= 'F');



/*! Decodes a URL string (ripped from rosetta)
    \param s string to decode
    \param dec preallocated buffer to store decoded result in
    \return <0 on failure
 */
  int
urldecode (const char *s, char *dec)
{
  
  
  
  
    
    {
      
      
	
      
      else if (c == '%'
	       && (!ishex (*s++) || 
		   || 
	
      
	
    
  

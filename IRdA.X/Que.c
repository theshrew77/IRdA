

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "main.h"
#include "Que.h"

/**
 ******************************************************************************
 * @name   	: int8_t  QInit( t_Q *pQ )
 * @brief  	: Initializes the t_Q structure pointed to by *pQ.
 * @author	: Kent Dieball
 ******************************************************************************
 * INPUTS:
 * 	@param    *pQ - t_Q structure pointer
 *
 * OUTPUTS:
 *  @param	  *pQ structure is initialized to default values.
 *
 * GLOBALS:
 * 	None
 * 	@retval   TRUE
 * ****************************************************************************
 */
int8_t  QInit( t_Q *pQ )
{
  int16_t i;
  pQ->In = 0;
  pQ->Out = 0;
  for (i=0;i<Q_MAX; i++)
  {
	  pQ->Data[i] = 0;
  }
  return(TRUE);
}

/**
 ******************************************************************************
 * @name   	: int8_t  QIn( int8_t Src, t_Q *pQ )
 * @brief  	: Places a value in the queue and increments In index
 * 			      If queue is full, the function returns -1
 * @author	: Kent Dieball
 ******************************************************************************
 * INPUTS:
 * 	@param    Src	  value to be placed in the queue.
 * 	@param    *pQ	  queue to hold the new value.
 *
 * OUTPUTS:
 *  @param	  pQ->In   The index to the position in queue.
 *
 * GLOBALS:
 * 	None
 * 	@retval
 * ****************************************************************************
 */
int8_t  QIn( int8_t Src, t_Q *pQ )
{
  int8_t next;

  next = (pQ->In + 1) % Q_MAX;  // get the next available queue slot
  if ( next == pQ->Out )
  {
    next = -1;                  // buffer is full
  }
  else
  {
    pQ->In = next;
    pQ->Data[pQ->In] = Src;
  }
  return(next);
}


/**
 ******************************************************************************
 * @name   	: int8_t  QOut( int8_t *Dest, t_Q *pQ )
 * @brief  	: Retrieves a value in the queue and manages the Out index.
 * @author	: Kent Dieball
 ******************************************************************************
 * INPUTS:
 * 	@param  *Dest  - pointer to the destination for the value from the queue.
 * 	@param  *pQ    - t_Q structure pointer to the queue.
 *
 * OUTPUTS:
 *  @retval on Success - TRUE
 *          on Failure - FALSE, no new entries
 *
 * GLOBALS:
 * 	None
 * 	@retval   TRUE
 * ****************************************************************************
 */
int8_t  QOut( int8_t *Dest, t_Q *pQ )
{
  if ( pQ->Out == pQ->In ) {              // if equal, then no new data
    return( FALSE );
  }
  pQ->Out++;
  pQ->Out = pQ->Out % Q_MAX;
  *Dest = pQ->Data[pQ->Out];
  return( TRUE );
}


/**
 ******************************************************************************
 * @name   	: int8_t  QChkQ( t_Q *pQ )
 * @brief   : Checks the queue for new entries
 * @author	: Kent Dieball
 ******************************************************************************
 * INPUTS:
 *  @param  *pQ    - t_Q structure pointer
 *
 * OUTPUTS:
 *  @retval TRUE   - data is available in the queue.
 *          FALSE  - data is NOT available in queue.
 *
 * GLOBALS:
 * 	None
 * 	@retval   TRUE
 * ****************************************************************************
 */
int8_t  QChkQ( t_Q *pQ )
{
  if ( pQ->Out == pQ->In )
  {
    return( FALSE );                      // if equal, then no new data
  }
  else
  {
    return( TRUE );
  }
}

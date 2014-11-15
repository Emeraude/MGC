#include <stdlib.h>
#include "mgc.h"

t_mgc_list	*mgc_list = NULL;

static void	_free_all()
{
  t_mgc_list	*tmp;
  t_mgc_list	*rm;

  tmp = mgc_list;
  while (tmp)
    {
      rm = tmp;
      tmp = tmp->next;
      free(rm->ptr);
      free(rm);
    }
}

void		*mmalloc(size_t size)
{
  t_mgc_list	*new;
  void		*allocated;
  static int	first = 1;

  if (first)
    {
      atexit(&free_all);
      --first;
    }
  if ((new = malloc(sizeof(t_mgc_list))) == NULL
      || (allocated = malloc(size)) == NULL)
    return (NULL);
  new->ptr = allocated;
  new->next = mgc_list;
  new->prev = NULL;
  if (mgc_list)
    mgc_list->prev = new;
  mgc_list = new;
  return (allocated);
}

void		mfree(void *ptr)
{
  t_mgc_list	*tmp;

  tmp = mgc_list;
  while (tmp && tmp->ptr != ptr)
    tmp = tmp->next;
  if (tmp)
    {
      if (tmp->prev)
	tmp->prev->next = tmp->next;
      else
	mgc_list = tmp->next;
      if (tmp->next)
	tmp->next->prev = tmp->prev;
      free(tmp->ptr);
      free(tmp);
    }
}

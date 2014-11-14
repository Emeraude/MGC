#ifndef MGC_H_
# define MGC_H_

# include <stddef.h>

typedef struct		s_mgc_list
{
  void			*ptr;
  struct s_mgc_list	*next;
  struct s_mgc_list	*prev;
}			t_mgc_list;

void			*mmalloc(size_t size);
void			mfree(void *ptr);

#endif

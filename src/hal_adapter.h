#ifndef HAL_ADAPTER_H
#define HAL_ADAPTER_H
 
void set_extended(bool on); /*forward*/
bool read_extended_switch(void);

void set_SHRINKED(bool on); /*backwards*/  
bool read_SHRINKED_switch(void); 
 
unsigned int get_tick_ms(void);
 
#endif 
 
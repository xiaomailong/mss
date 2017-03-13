#include "RSSP_I_unibase.h"

uint32_t LFSR_Add(uint32_t x, uint32_t y, uint32_t mask)
{
    uint32_t val = x ^ y;
    uint8_t carry = 0;
	int i;

    for(i=0; i<32; i++)
    {
        if((val & 0x80000000) != 0)
        {
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        val = val << 1;

        if(1 == carry)
        {
            val = val ^ mask;
        }
        else{}
    }

    return val;
}

uint32_t LFSR_Post(uint32_t x, uint32_t y, uint32_t mask)
{
    uint32_t val = x ^ y;
    uint32_t val_init = val;
    uint8_t carry = 0;
    int i;

    for(i = 0;i < 32; i++)
    {
        if(carry == (val & 1))
        {
            val = val ^ mask;
        }
        else{}

        val = val >> 1;
        if(carry == 1)
        {
            val = val | 0x80000000;
        }
        else
        {
            val = val | 0;
        }
    }

    val = val ^ val_init;

    return val;
}

/* @param last_counter 最近一次接收到的RSD的序列号
 * @param rcv_counter  最新接收到的RSD的序列号
 * @param max_loss     最大容忍序列号偏差
 */
uint8_t compareCounters(uint32_t last_counter, uint32_t rcv_counter, uint8_t max_loss)
{
    uint8_t ret = 0;
    uint8_t loss;

    if (last_counter < rcv_counter)
    {
        loss = rcv_counter - last_counter;
        if (loss < max_loss)
        {
            ret = loss;
        }
        else
        {
            ret = 0;
        }
    }
    else
    {   
        ret = 0;
    }
    return ret;
}

uint16_t forwardTimer(local_time_param_t *timer)
{
    uint16_t ret = 1;

    if (NULL == timer)
    {
        ret = 0;
    }
    else
    {
        timer->time_counter = (timer->time_counter) + 1;
        timer->time_stamp_1 = LFSR_Add(timer->time_stamp_1, 0, MASK_1);
        timer->time_stamp_2 = LFSR_Add(timer->time_stamp_2, 0, MASK_2);
    }

    return ret;
}

void set_tick_timer(local_time_param_t *local, uint32_t now)
{
    local->sse_start = now;
    local->sse_timeout = 0;
}

void reset_tick_timer(local_time_param_t *local)
{
    local->sse_start = 0;
    local->sse_timeout = 0;
}

void stop_tick_timer(local_time_param_t *local, uint32_t now)
{
    local->sse_timeout = now - local->sse_start;
}

uint32_t SEQENQ_calculator(uint32_t sid, uint32_t ts_e)
{
    return (sid ^ ts_e);
}

uint32_t SEQINIT_calculator(uint32_t senq, uint32_t sid, uint32_t ts_r, uint32_t dataver)
{
    uint32_t seqinit = senq ^ sid ^ ts_r ^ dataver; 
    return seqinit;
}

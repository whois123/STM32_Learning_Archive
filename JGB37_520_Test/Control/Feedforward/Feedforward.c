#include "Feedforward.h"

/**
 * @brief  初始化前馈控制器
 * @param  ff       前馈结构体指针
 * @param  Kv       速度前馈系数
 * @param  Ka       加速度前馈系数
 * @param  dt       调用周期 (秒)
 * @param  max_out  最大输出限幅
 */
void FF_Init(Feedforward_t *ff, float Kv, float Ka, float dt, float max_out)
{
    if (!ff) return;
    
    ff->Kv = Kv;
    ff->Ka = Ka;
    ff->dt = dt;
    ff->max_out = max_out;
    
    FF_Clear(ff);
}

/**
 * @brief  计算前馈输出
 * @param  ff              前馈结构体指针
 * @param  ref_speed       当前周期的目标速度
 * @param  ref_accel_feed  目标加速度 (若有运动规划可直接传入，若无则传 0 并在内部差分)
 * @retval float           前馈计算得出的控制量
 */
float FF_Calculate(Feedforward_t *ff, float ref_speed, float ref_accel_feed)
{
    if (!ff) return 0.0f;

    /* 速度前馈分量 */
    ff->out_v = ff->Kv * ref_speed;

    /* 加速度前馈分量计算 */
    float target_accel = 0.0f;
    if (ref_accel_feed != 0.0f)
    {
        /* 优先使用外部运动规划器传入的平滑加速度 */
        target_accel = ref_accel_feed;
    }
    else
    {
        /* 若无外部传入，则通过对目标速度的后向差分估算目标加速度 */
        target_accel = (ref_speed - ff->last_ref) / ff->dt;
    }
    
    ff->out_a = ff->Ka * target_accel;
    
    /* 汇总并限幅 */
    ff->out_total = ff->out_v + ff->out_a;
    
    if (ff->out_total > ff->max_out)       ff->out_total = ff->max_out;
    else if (ff->out_total < -ff->max_out) ff->out_total = -ff->max_out;

    /* 状态更新 */
    ff->last_ref = ref_speed;

    return ff->out_total;
}

/**
 * @brief  清空前馈历史状态
 */
void FF_Clear(Feedforward_t *ff)
{
    if (!ff) return;
    ff->last_ref  = 0.0f;
    ff->out_v     = 0.0f;
    ff->out_a     = 0.0f;
    ff->out_total = 0.0f;
}
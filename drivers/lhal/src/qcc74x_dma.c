#include "qcc74x_dma.h"
#include "qcc74x_l1c.h"
#include "hardware/dma_reg.h"

struct qcc74x_dma_irq_callback {
    void (*handler)(void *arg);
    void *arg;
};

#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
const uint32_t dma_base[] = { 0x4000C000 };
struct qcc74x_dma_irq_callback dma_callback[1][8];
#elif defined(QCC743)
const uint32_t dma_base[] = { 0x2000C000 };
struct qcc74x_dma_irq_callback dma_callback[1][4];
#elif defined(QCC74x_undef)
const uint32_t dma_base[] = { 0x2000C000 };
struct qcc74x_dma_irq_callback dma_callback[1][8];
#elif defined(QCC74x_undef) || defined(QCC74x_undef)
const uint32_t dma_base[] = { 0x2000C000, 0x20071000, 0x30001000 };
struct qcc74x_dma_irq_callback dma_callback[3][8];
#elif defined(QCC74x_undef)
const uint32_t dma_base[] = { 0x20081000 };
struct qcc74x_dma_irq_callback dma_callback[1][8];
#elif defined(QCC74x_undef)
const uint32_t dma_base[] = { 0x20081000, 0x20086000, 0x000C0000 };
struct qcc74x_dma_irq_callback dma_callback[3][8];
#endif

void dma0_isr(int irq, void *arg)
{
    uint32_t regval;

    regval = getreg32(dma_base[0] + DMA_INTTCSTATUS_OFFSET);
    putreg32(regval, dma_base[0] + DMA_INTTCCLEAR_OFFSET);

    for (uint8_t i = 0; i < 8; i++) {
        if (regval & (1 << i)) {
            dma_callback[0][i].handler(dma_callback[0][i].arg);
        }
    }
}

#if defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
void dma1_isr(int irq, void *arg)
{
    uint32_t regval;

    regval = getreg32(dma_base[1] + DMA_INTTCSTATUS_OFFSET);
    putreg32(regval, dma_base[1] + DMA_INTTCCLEAR_OFFSET);

    for (uint8_t i = 0; i < 8; i++) {
        if (regval & (1 << i)) {
            dma_callback[1][i].handler(dma_callback[1][i].arg);
        }
    }
}

void dma2_isr(int irq, void *arg)
{
    uint32_t regval;

    regval = getreg32(dma_base[2] + DMA_INTTCSTATUS_OFFSET);
    putreg32(regval, dma_base[2] + DMA_INTTCCLEAR_OFFSET);

    for (uint8_t i = 0; i < 8; i++) {
        if (regval & (1 << i)) {
            dma_callback[2][i].handler(dma_callback[2][i].arg);
        }
    }
}
#endif

void qcc74x_dma_channel_init(struct qcc74x_device_s *dev, const struct qcc74x_dma_channel_config_s *config)
{
    LHAL_PARAM_ASSERT(dev);
    LHAL_PARAM_ASSERT(IS_DMA_DIRECTION(config->direction));
    LHAL_PARAM_ASSERT(IS_DMA_BURST_COUNT(config->src_burst_count));
    LHAL_PARAM_ASSERT(IS_DMA_BURST_COUNT(config->dst_burst_count));
    LHAL_PARAM_ASSERT(IS_DMA_DATA_WIDTH(config->src_width));
    LHAL_PARAM_ASSERT(IS_DMA_DATA_WIDTH(config->dst_width));

#ifdef romapi_qcc74x_dma_channel_init
    romapi_qcc74x_dma_channel_init(dev, config);
#else
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    /* dma global enable */
    regval = getreg32(dma_base[dev->idx] + DMA_TOP_CONFIG_OFFSET);
    regval |= DMA_E;
    putreg32(regval, dma_base[dev->idx] + DMA_TOP_CONFIG_OFFSET);

    /* dma channel disable */
    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    regval &= ~DMA_E;
    putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);

#if defined(QCC74x_undef)
    regval = 0;
#else
    regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
    regval &= DMA_DST_ADD_MODE | DMA_DST_MIN_MODE | DMA_FIX_CNT_MASK;
#endif

    if (config->src_addr_inc) {
        regval |= DMA_SI;
    }
    if (config->dst_addr_inc) {
        regval |= DMA_DI;
    }

    regval |= (config->src_width << DMA_SWIDTH_SHIFT);
    regval |= (config->dst_width << DMA_DWIDTH_SHIFT);
    regval |= (config->src_burst_count << DMA_SBSIZE_SHIFT);
    regval |= (config->dst_burst_count << DMA_DBSIZE_SHIFT);
    putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);

    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    regval &= ~DMA_SRCPERIPHERAL_MASK;
    regval &= ~DMA_DSTPERIPHERAL_MASK;
    regval &= ~DMA_FLOWCNTRL_MASK;
    regval &= ~DMA_LLICOUNTER_MASK;
    regval |= (config->src_req << DMA_SRCPERIPHERAL_SHIFT);
    regval |= (config->dst_req << DMA_DSTPERIPHERAL_SHIFT);
    regval |= (config->direction << DMA_FLOWCNTRL_SHIFT);
    putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);

    /* enable dma error and tc interrupt */
    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    regval |= (DMA_ITC | DMA_IE);
    putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);

    regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
    regval &= ~DMA_I;
    putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);

    /* clear irq status */
    putreg32(1 << dev->sub_idx, dma_base[dev->idx] + DMA_INTTCCLEAR_OFFSET);
    putreg32(1 << dev->sub_idx, dma_base[dev->idx] + DMA_INTERRCLR_OFFSET);
#endif
}

void qcc74x_dma_channel_deinit(struct qcc74x_device_s *dev)
{
#ifdef romapi_qcc74x_dma_channel_deinit
    romapi_qcc74x_dma_channel_deinit(dev);
#else
    qcc74x_dma_channel_stop(dev);
    qcc74x_dma_channel_tcint_mask(dev, true);
#endif
}

__UNUSED static void qcc74x_dma_lli_config(struct qcc74x_device_s *dev,
                         struct qcc74x_dma_channel_lli_pool_s *lli_pool,
                         uint32_t lli_count,
                         uint32_t src_addr,
                         uint32_t dst_addr,
                         uint32_t transfer_offset,
                         uint32_t last_transfer_len)
{
#ifdef romapi_qcc74x_dma_lli_config
    romapi_qcc74x_dma_lli_config(dev,
                               lli_pool,
                               lli_count,
                               src_addr,
                               dst_addr,
                               transfer_offset,
                               last_transfer_len);
#else
    uint32_t channel_base;
    union qcc74x_dma_lli_control_s dma_ctrl_cfg;

    channel_base = dev->reg_base;

    dma_ctrl_cfg = (union qcc74x_dma_lli_control_s)getreg32(channel_base + DMA_CxCONTROL_OFFSET);

    dma_ctrl_cfg.bits.TransferSize = 4064;
    dma_ctrl_cfg.bits.I = 0;

    /* nbytes will be integer multiple of 4064*n or 4064*2*n or 4064*4*n,(n>0) */
    for (uint32_t i = 0; i < lli_count; i++) {
        lli_pool[i].src_addr = src_addr;
        lli_pool[i].dst_addr = dst_addr;
        lli_pool[i].nextlli = 0;

        if (dma_ctrl_cfg.bits.SI) {
            src_addr += transfer_offset;
        }

        if (dma_ctrl_cfg.bits.DI) {
            dst_addr += transfer_offset;
        }

        if (i == lli_count - 1) {
            dma_ctrl_cfg.bits.TransferSize = last_transfer_len;
            dma_ctrl_cfg.bits.I = 1;
        }

        if (i) {
            lli_pool[i - 1].nextlli = (uint32_t)(uintptr_t)&lli_pool[i];
        }

        lli_pool[i].control = dma_ctrl_cfg;
    }
#endif
}

int qcc74x_dma_channel_lli_reload(struct qcc74x_device_s *dev, struct qcc74x_dma_channel_lli_pool_s *lli_pool, uint32_t max_lli_count, struct qcc74x_dma_channel_lli_transfer_s *transfer, uint32_t count)
{
#ifdef romapi_qcc74x_dma_channel_lli_reload
    return romapi_qcc74x_dma_channel_lli_reload(dev, lli_pool, max_lli_count, transfer, count);
#else
    uint32_t channel_base;
    uint32_t actual_transfer_offset = 0;
    uint32_t actual_transfer_len = 0;
    uint32_t last_transfer_len = 0;
    uint32_t current_lli_count = 0;
    uint32_t lli_count_used_offset = 0;
    union qcc74x_dma_lli_control_s dma_ctrl_cfg;

    channel_base = dev->reg_base;

    dma_ctrl_cfg = (union qcc74x_dma_lli_control_s)getreg32(channel_base + DMA_CxCONTROL_OFFSET);

    switch (dma_ctrl_cfg.bits.SWidth) {
        case DMA_DATA_WIDTH_8BIT:
            actual_transfer_offset = 4064;
            break;
        case DMA_DATA_WIDTH_16BIT:
            actual_transfer_offset = 4064 << 1;
            break;
        case DMA_DATA_WIDTH_32BIT:
            actual_transfer_offset = 4064 << 2;
            break;
        default:
            break;
    }

    for (size_t i = 0; i < count; i++) {
        switch (dma_ctrl_cfg.bits.SWidth) {
            case DMA_DATA_WIDTH_8BIT:
                actual_transfer_len = transfer[i].nbytes;
                break;
            case DMA_DATA_WIDTH_16BIT:
                if (transfer[i].nbytes % 2) {
                    return -1;
                }
                actual_transfer_len = transfer[i].nbytes >> 1;
                break;
            case DMA_DATA_WIDTH_32BIT:
                if (transfer[i].nbytes % 4) {
                    return -1;
                }
                actual_transfer_len = transfer[i].nbytes >> 2;
                break;

            default:
                break;
        }

        current_lli_count = actual_transfer_len / 4064 + 1;
        last_transfer_len = actual_transfer_len % 4064;

        /* The maximum transfer capacity of the last node is 4095 */
        if (current_lli_count > 1 && last_transfer_len < (4095 - 4064)) {
            current_lli_count--;
            last_transfer_len += 4064;
        }

        qcc74x_dma_lli_config(dev, &lli_pool[lli_count_used_offset], current_lli_count, transfer[i].src_addr, transfer[i].dst_addr, actual_transfer_offset, last_transfer_len);
        if (i) {
            lli_pool[lli_count_used_offset - 1].nextlli = (uint32_t)(uintptr_t)&lli_pool[lli_count_used_offset];
        }
        lli_count_used_offset += current_lli_count;

        if (lli_count_used_offset > max_lli_count) {
            return -ENOMEM;
        }
    }

    putreg32(lli_pool[0].src_addr, channel_base + DMA_CxSRCADDR_OFFSET);
    putreg32(lli_pool[0].dst_addr, channel_base + DMA_CxDSTADDR_OFFSET);
    putreg32(lli_pool[0].nextlli, channel_base + DMA_CxLLI_OFFSET);
    putreg32(lli_pool[0].control.WORD, channel_base + DMA_CxCONTROL_OFFSET);
#if defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    /* clean cache, DMA does not pass through the cache */
    qcc74x_l1c_dcache_clean_range((uint32_t *)(uintptr_t)lli_pool, sizeof(struct qcc74x_dma_channel_lli_pool_s) * lli_count_used_offset);
#endif
    return lli_count_used_offset;
#endif
}

#if defined(QCC74x_undef)
int qcc74x_dma_channel_lli_insert(struct qcc74x_device_s *dev, struct qcc74x_dma_channel_lli_pool_s *lli_pool, uint32_t max_lli_count, struct qcc74x_dma_channel_lli_transfer_s *transfer, uint32_t count)
{
#ifdef romapi_qcc74x_dma_channel_lli_insert
    return romapi_qcc74x_dma_channel_lli_insert(dev, lli_pool, max_lli_count, transfer, count);
#else
    uint32_t channel_base;
    uint32_t actual_transfer_offset = 0;
    uint32_t actual_transfer_len = 0;
    uint32_t last_transfer_len = 0;
    uint32_t current_lli_count = 0;
    uint32_t lli_count_used_offset = 0;
    union qcc74x_dma_lli_control_s dma_ctrl_cfg;

    channel_base = dev->reg_base;

    dma_ctrl_cfg = (union qcc74x_dma_lli_control_s)getreg32(channel_base + DMA_CxCONTROL_OFFSET);

    qcc74x_dma_feature_control(dev, DMA_CMD_SET_LLI_MUTEX, 1);

    if (qcc74x_dma_feature_control(dev, DMA_CMD_GET_LLI_MUTEX_STATUS, 0) == DMA_LLI_MUTEX_UNAVAILABLE) {
        return -1;
    }

    for (lli_count_used_offset = 0; lli_count_used_offset < max_lli_count; lli_count_used_offset++) {
        if (lli_pool[lli_count_used_offset].nextlli == 0) {
            break;
        }
    }
    if (count) {
        lli_pool[lli_count_used_offset].nextlli = (uint32_t)(uintptr_t)&lli_pool[lli_count_used_offset + 1];
        if (qcc74x_dma_feature_control(dev, DMA_CMD_GET_LLI_MUTEX_STATUS, 0) == DMA_LLI_MUTEX_LAST_NODE) {
            putreg32(lli_pool[lli_count_used_offset].nextlli, channel_base + DMA_CxLLI_OFFSET);
        }
        lli_count_used_offset++;
    }

    switch (dma_ctrl_cfg.bits.SWidth) {
        case DMA_DATA_WIDTH_8BIT:
            actual_transfer_offset = 4064;
            break;
        case DMA_DATA_WIDTH_16BIT:
            actual_transfer_offset = 4064 << 1;
            break;
        case DMA_DATA_WIDTH_32BIT:
            actual_transfer_offset = 4064 << 2;
            break;
        default:
            break;
    }

    for (size_t i = 0; i < count; i++) {
        switch (dma_ctrl_cfg.bits.SWidth) {
            case DMA_DATA_WIDTH_8BIT:
                actual_transfer_len = transfer[i].nbytes;
                break;
            case DMA_DATA_WIDTH_16BIT:
                if (transfer[i].nbytes % 2) {
                    return -1;
                }
                actual_transfer_len = transfer[i].nbytes >> 1;
                break;
            case DMA_DATA_WIDTH_32BIT:
                if (transfer[i].nbytes % 4) {
                    return -1;
                }
                actual_transfer_len = transfer[i].nbytes >> 2;
                break;

            default:
                break;
        }

        current_lli_count = actual_transfer_len / 4064 + 1;
        last_transfer_len = actual_transfer_len % 4064;

        /* The maximum transfer capacity of the last node is 4095 */
        if (current_lli_count > 1 && last_transfer_len < (4095 - 4064)) {
            current_lli_count--;
            last_transfer_len += 4064;
        }

        qcc74x_dma_lli_config(dev, &lli_pool[lli_count_used_offset], current_lli_count, transfer[i].src_addr, transfer[i].dst_addr, actual_transfer_offset, last_transfer_len);
        if (i) {
            lli_pool[lli_count_used_offset - 1].nextlli = (uint32_t)(uintptr_t)&lli_pool[lli_count_used_offset];
        }
        lli_count_used_offset += current_lli_count;

        if (lli_count_used_offset > max_lli_count) {
            return -ENOMEM;
        }
    }

    /* clean cache, DMA does not pass through the cache */
    qcc74x_l1c_dcache_clean_range((uint32_t *)(uintptr_t)lli_pool, sizeof(struct qcc74x_dma_channel_lli_pool_s) * lli_count_used_offset);

    qcc74x_dma_feature_control(dev, DMA_CMD_SET_LLI_MUTEX, 0);

    return lli_count_used_offset;
#endif
}
#endif

void qcc74x_dma_channel_lli_link_head(struct qcc74x_device_s *dev,
                                    struct qcc74x_dma_channel_lli_pool_s *lli_pool,
                                    uint32_t used_lli_count)
{
#ifdef romapi_qcc74x_dma_channel_lli_link_head
    romapi_qcc74x_dma_channel_lli_link_head(dev, lli_pool, used_lli_count);
#else
    uint32_t channel_base;

    channel_base = dev->reg_base;

    lli_pool[used_lli_count - 1].nextlli = (uint32_t)(uintptr_t)&lli_pool[0];

    putreg32(lli_pool[0].nextlli, channel_base + DMA_CxLLI_OFFSET);
#if defined(QCC743) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef) || defined(QCC74x_undef)
    /* clean cache, DMA does not pass through the cache */
    qcc74x_l1c_dcache_clean_range((uint32_t *)lli_pool, sizeof(struct qcc74x_dma_channel_lli_pool_s) * used_lli_count);
#endif
#endif
}

void qcc74x_dma_channel_start(struct qcc74x_device_s *dev)
{
#ifdef romapi_qcc74x_dma_channel_start
    romapi_qcc74x_dma_channel_start(dev);
#else
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    /* dma channel enable */
    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    regval |= DMA_E;
    putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);
#endif
}

void qcc74x_dma_channel_stop(struct qcc74x_device_s *dev)
{
#ifdef romapi_qcc74x_dma_channel_stop
    romapi_qcc74x_dma_channel_stop(dev);
#else
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    /* dma channel disable */
    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    regval &= ~DMA_E;
    putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);
#endif
}

bool qcc74x_dma_channel_isbusy(struct qcc74x_device_s *dev)
{
#ifdef romapi_qcc74x_dma_channel_isbusy
    return romapi_qcc74x_dma_channel_isbusy(dev);
#else
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
    if (regval & (1 << 0)) {
        return true;
    } else {
        return false;
    }
#endif
}

void qcc74x_dma_channel_tcint_mask(struct qcc74x_device_s *dev, bool mask)
{
#ifdef romapi_qcc74x_dma_channel_tcint_mask
    romapi_qcc74x_dma_channel_tcint_mask(dev, mask);
#else
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    if (mask) {
        regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
        regval |= DMA_ITC;
        putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);
    } else {
        regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
        regval &= ~DMA_ITC;
        putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);
    }
#endif
}

void qcc74x_dma_channel_irq_attach(struct qcc74x_device_s *dev, void (*callback)(void *arg), void *arg)
{
    dma_callback[dev->idx][dev->sub_idx].handler = callback;
    dma_callback[dev->idx][dev->sub_idx].arg = arg;

    qcc74x_dma_channel_tcint_mask(dev, false);

    if (dev->idx == 0) {
        qcc74x_irq_attach(dev->irq_num, dma0_isr, NULL);
        qcc74x_irq_enable(dev->irq_num);
    }
#if (defined(QCC74x_undef) || defined(QCC74x_undef)) && (defined(CPU_M0) || defined(CPU_LP)) || defined(QCC74x_undef)
    else if (dev->idx == 1) {
        qcc74x_irq_attach(dev->irq_num, dma1_isr, NULL);
        qcc74x_irq_enable(dev->irq_num);
    }
#endif
#if ((defined(QCC74x_undef) || defined(QCC74x_undef)) && defined(CPU_D0)) || defined(QCC74x_undef)
    else if (dev->idx == 2) {
        qcc74x_irq_attach(dev->irq_num, dma2_isr, NULL);
        qcc74x_irq_enable(dev->irq_num);
    }
#endif
}

void qcc74x_dma_channel_irq_detach(struct qcc74x_device_s *dev)
{
    dma_callback[dev->idx][dev->sub_idx].handler = NULL;
    dma_callback[dev->idx][dev->sub_idx].arg = NULL;

    qcc74x_dma_channel_tcint_mask(dev, true);
}

bool qcc74x_dma_channel_get_tcint_status(struct qcc74x_device_s *dev)
{
#ifdef romapi_qcc74x_dma_channel_get_tcint_status
    return romapi_qcc74x_dma_channel_get_tcint_status(dev);
#else
    uint32_t regval;

    regval = getreg32(dma_base[dev->idx] + DMA_INTTCSTATUS_OFFSET);
    if (regval & (1 << dev->sub_idx)) {
        return true;
    } else {
        return false;
    }
#endif
}

void qcc74x_dma_channel_tcint_clear(struct qcc74x_device_s *dev)
{
#ifdef romapi_qcc74x_dma_channel_tcint_clear
    romapi_qcc74x_dma_channel_tcint_clear(dev);
#else
    putreg32(1 << dev->sub_idx, dma_base[dev->idx] + DMA_INTTCCLEAR_OFFSET);
#endif
}

int qcc74x_rx_cycle_dma_init(struct qcc74x_rx_cycle_dma *rx_dma,
                           struct qcc74x_device_s *dma_ch,
                           struct qcc74x_dma_channel_lli_pool_s *rx_llipool,
                           uint8_t rx_llipool_size,
                           uint32_t src_addr,
                           uint8_t *dst_buf,
                           uint32_t dst_buf_size,
                           void (*copy)(uint8_t *data, uint32_t len))
{
#ifdef romapi_qcc74x_rx_cycle_dma_init
    return romapi_qcc74x_rx_cycle_dma_init(rx_dma,
                                         dma_ch,
                                         rx_llipool,
                                         rx_llipool_size,
                                         src_addr,
                                         dst_buf,
                                         dst_buf_size,
                                         copy);
#else
    struct qcc74x_dma_channel_lli_transfer_s rx_transfers[2];

    rx_dma->dst_buf = dst_buf;
    rx_dma->dst_buf_size = dst_buf_size;
    rx_dma->dma_last_lli_count = 0;
    rx_dma->read_ptr = dst_buf;
    rx_dma->dma_ch = dma_ch;
    rx_dma->copy = copy;

    rx_transfers[0].src_addr = (uint32_t)(uintptr_t)src_addr;
    rx_transfers[0].dst_addr = (uint32_t)(uintptr_t)dst_buf;
    rx_transfers[0].nbytes = dst_buf_size / 2;

    rx_transfers[1].src_addr = (uint32_t)(uintptr_t)src_addr;
    rx_transfers[1].dst_addr = (uint32_t)(uintptr_t)dst_buf + dst_buf_size / 2;
    rx_transfers[1].nbytes = dst_buf_size / 2;

    int used_count = qcc74x_dma_channel_lli_reload(dma_ch, rx_llipool, rx_llipool_size, rx_transfers, 2);

    if (used_count < 0) {
        return -1;
    }

    qcc74x_dma_channel_lli_link_head(dma_ch, rx_llipool, used_count);
    return 0;
#endif
}

void qcc74x_rx_cycle_dma_process(struct qcc74x_rx_cycle_dma *rx_dma, bool in_dma_isr)
{
#ifdef romapi_qcc74x_rx_cycle_dma_process
    romapi_qcc74x_rx_cycle_dma_process(rx_dma, in_dma_isr);
#else
    uint16_t length;
    uint32_t dma_lli_count;
    uint8_t *write_ptr;

    write_ptr = (uint8_t *)(uintptr_t)qcc74x_dma_feature_control(rx_dma->dma_ch, DMA_CMD_GET_LLI_DSTADDR, 0);
    dma_lli_count = qcc74x_dma_feature_control(rx_dma->dma_ch, DMA_CMD_GET_LLI_COUNT, 0);

    if (write_ptr > rx_dma->read_ptr) {
        length = write_ptr - rx_dma->read_ptr;

        rx_dma->copy(rx_dma->read_ptr, length);

        // printf("[1] w:%08x, r:%p,len:%d,lli count:%d\r\n",
        //        write_ptr,
        //        rx_dma->read_ptr,
        //        length,
        //        dma_lli_count);
    } else {
        if ((write_ptr != rx_dma->read_ptr) || (dma_lli_count != rx_dma->dma_last_lli_count)) {
            /* copy the data from read_ptr to tail */
            length = rx_dma->dst_buf + rx_dma->dst_buf_size - rx_dma->read_ptr;
            rx_dma->copy(rx_dma->read_ptr, length);

            /* copy the data from head to write_ptr */
            rx_dma->copy(rx_dma->dst_buf, (write_ptr - rx_dma->dst_buf));
            length += (write_ptr - rx_dma->dst_buf);

            // printf("[2] w:%08x, r:%p,len:%d,lli count:%d\r\n",
            //        write_ptr,
            //        rx_dma->read_ptr,
            //        length,
            //        dma_lli_count);
        }
    }

    rx_dma->read_ptr = write_ptr;
    rx_dma->dma_last_lli_count = dma_lli_count;
#endif
}

int qcc74x_dma_feature_control(struct qcc74x_device_s *dev, int cmd, size_t arg)
{
#ifdef romapi_qcc74x_dma_feature_control
    return romapi_qcc74x_dma_feature_control(dev, cmd, arg);
#else
    int ret = 0;
    uint32_t regval;
    uint32_t channel_base;

    channel_base = dev->reg_base;

    switch (cmd) {
        case DMA_CMD_SET_SRCADDR_INCREMENT:
            regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
            if (arg) {
                regval |= DMA_SI;
            } else {
                regval &= ~DMA_SI;
            }
            putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);
            break;

        case DMA_CMD_SET_DSTADDR_INCREMENT:
            regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
            if (arg) {
                regval |= DMA_DI;
            } else {
                regval &= ~DMA_DI;
            }
            putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);
            break;

#if !defined(QCC74x_undef)
        case DMA_CMD_SET_ADD_MODE:
            regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
            if (arg) {
                regval |= DMA_DST_ADD_MODE;
            } else {
                regval &= ~DMA_DST_ADD_MODE;
            }
            putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);
            break;

        case DMA_CMD_SET_REDUCE_MODE:
            regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
            if (arg) {
                regval |= DMA_DST_MIN_MODE;
                regval &= ~DMA_FIX_CNT_MASK;
                regval |= (arg & 0x7) << DMA_FIX_CNT_SHIFT;
            } else {
                regval &= ~DMA_DST_MIN_MODE;
            }
            putreg32(regval, channel_base + DMA_CxCONTROL_OFFSET);
            break;
#endif
        case DMA_CMD_SET_LLI_CONFIG:
            arch_memcpy4((uint32_t *)(uintptr_t)(channel_base + DMA_CxSRCADDR_OFFSET), (uint32_t *)arg, 4);
            break;
        case DMA_CMD_GET_LLI_SRCADDR:
            return getreg32(channel_base + DMA_CxSRCADDR_OFFSET);
        case DMA_CMD_GET_LLI_DSTADDR:
            return getreg32(channel_base + DMA_CxDSTADDR_OFFSET);
        case DMA_CMD_GET_LLI_CONTROL:
            return getreg32(channel_base + DMA_CxCONTROL_OFFSET);
        case DMA_CMD_GET_LLI_COUNT:
            return (getreg32(channel_base + DMA_CxCONFIG_OFFSET) & DMA_LLICOUNTER_MASK) >> DMA_LLICOUNTER_SHIFT;
        case DMA_CMD_GET_TRANSFER_PENDING:
            return (getreg32(channel_base + DMA_CxCONTROL_OFFSET) & DMA_TRANSFERSIZE_MASK) >> DMA_TRANSFERSIZE_SHIFT;

#if defined(QCC74x_undef)
        case DMA_CMD_SET_LLI_MUTEX:
            regval = getreg32(channel_base + DMA_CxCONFIG_OFFSET);
            if (arg) {
                regval |= DMA_LLI_MUTEX;
            } else {
                regval &= ~DMA_LLI_MUTEX;
                regval |= DMA_E;
            }
            putreg32(regval, channel_base + DMA_CxCONFIG_OFFSET);
            break;

        case DMA_CMD_GET_LLI_MUTEX_STATUS:
            regval = getreg32(channel_base + DMA_CxCONTROL_OFFSET);
            if (regval & DMA_LLI_VALID) {
                regval = getreg32(channel_base + DMA_CxLLI_OFFSET);
                if (regval == 0) {
                    ret = DMA_LLI_MUTEX_LAST_NODE;
                } else {
                    ret = DMA_LLI_MUTEX_NOT_LAST_NODE;
                }
            } else {
                ret = DMA_LLI_MUTEX_UNAVAILABLE;
            }
            break;

        case DMA_CMD_READ_HW_VERSION:
            regval = getreg32(dma_base[0] + DMA_HW_VERSION_OFFSET);
            ret = (regval & DMA_HW_VERSION_MASK) >> DMA_HW_VERSION_SHIFT;
            break;

        case DMA_CMD_READ_SW_USAGE:
            regval = getreg32(dma_base[0] + DMA_SW_USAGE_OFFSET);
            ret = (regval & DMA_SW_USAGE_MASK) >> DMA_SW_USAGE_SHIFT;
            break;

        case DMA_CMD_WRITE_SW_USAGE:
            regval = getreg32(dma_base[0] + DMA_SW_USAGE_OFFSET);
            regval &= ~DMA_SW_USAGE_MASK;
            regval |= ((arg << DMA_SW_USAGE_SHIFT) & DMA_SW_USAGE_MASK);
            putreg32(regval, dma_base[0] + DMA_SW_USAGE_OFFSET);
            break;
#endif

        default:
            ret = -EPERM;
            break;
    }
    return ret;
#endif
}

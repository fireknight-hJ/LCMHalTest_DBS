/**
* @brief  Read an amount of data in blocking mode from a specific memory address
* @param  hi2c Pointer to a I2C_HandleTypeDef structure that contains
*                the configuration information for the specified I2C.
* @param  DevAddress Target device address: The device 7 bits address value
*         in datasheet must be shifted to the left before calling the interface
* @param  MemAddress Internal memory address
* @param  MemAddSize Size of internal memory address
* @param  pData Pointer to data buffer
* @param  Size Amount of data to be sent
* @param  Timeout Timeout duration
* @retval HAL status
*/
HAL_StatusTypeDef HAL_I2C_Mem_Read(I2C_HandleTypeDef *hi2c, uint16_t DevAddress, uint16_t MemAddress,
                                   uint16_t MemAddSize, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
  /* Check the parameters */
  assert_param(IS_I2C_MEMADD_SIZE(MemAddSize));

  if (hi2c->State == HAL_I2C_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0U))
    {
      hi2c->ErrorCode = HAL_I2C_ERROR_INVALID_PARAM;
      return HAL_ERROR;
    }

    /* Process Locked */
    __HAL_LOCK(hi2c);

    /* Use HAL_BE_In to simulate data reception from stdin */
    int bytes_read = HAL_BE_In(pData, Size);
    
    if (bytes_read < 0)
    {
      /* Process Unlocked */
      __HAL_UNLOCK(hi2c);
      hi2c->State = HAL_I2C_STATE_READY;
      hi2c->Mode  = HAL_I2C_MODE_NONE;
      return HAL_ERROR;
    }

    /* Update transfer counters based on actual bytes read */
    hi2c->XferSize = bytes_read;
    hi2c->XferCount = bytes_read;

    hi2c->State = HAL_I2C_STATE_READY;
    hi2c->Mode  = HAL_I2C_MODE_NONE;

    /* Process Unlocked */
    __HAL_UNLOCK(hi2c);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}


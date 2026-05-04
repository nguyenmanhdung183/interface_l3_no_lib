xnap_return_et assign_hardcode_value_device_config_t(device_config_t *p_device_config)
{
    /* idx0: bitmask S */
    {
        p_device_config->bitmask = 0;
    }
    /* idx0: bitmask E */

    /* idx1: version S */
    {
        p_device_config->version = 127;
    }
    /* idx1: version E */

    /* idx2: rf_params S */
    {
        /* idx3: bitmask S */
        {
            p_device_config->rf_params.bitmask = 0;
        }
        /* idx3: bitmask E */

        /* idx4: id S */
        {
            p_device_config->rf_params.id = 500;
        }
        /* idx4: id E */

        /* idx5: num_bands S */
        {
            p_device_config->rf_params.num_bands = 0;
        }
        /* idx5: num_bands E */

        /* idx6: bands S */
        {
            for (int bands_index = 0; bands_index < p_device_config->rf_params.num_bands; bands_index++) // STRUCT array VARIABLE
            {
                p_device_config->rf_params.bands[bands_index].bitmask = 0;
                p_device_config->rf_params.bands[bands_index].band_id = 0;
                p_device_config->rf_params.bands[bands_index].frequency = 0;
                p_device_config->rf_params.bands[bands_index].optional_param_id = 0;
                p_device_config->rf_params.bands[bands_index].optional_param_data = 0;
            }
        }
        /* idx6: bands E */

        #if 1 /*idx7: config_blob S */
        {
            if (p_device_config->rf_params.bitmask & RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT)
            {
                for (int config_blob_index = 0; config_blob_index < 100; config_blob_index++) // STRUCT array FIXED
                {
                    p_device_config->rf_params.config_blob[config_blob_index].length = 2;

                    for (int i = 0; i < 2; i++)
                    {
                        p_device_config->rf_params.config_blob[config_blob_index].data[i] = (UInt16)(i + 1);
                    }
                }
            }
        }
        #endif /* idx7: config_blob E */
    }
    /* idx2: rf_params E */

    #if 1 /*idx8: extra_data_config S */
    {
        if (p_device_config->bitmask & CONFIG_PRESENT)
        {
            p_device_config->extra_data_config = 0;
        }
    }
    #endif /* idx8: extra_data_config E */

    #if 1 /*idx9: extra_data S */
    {
        if (p_device_config->bitmask & DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT)
        {
            for (int extra_data_index = 0; extra_data_index < 20; extra_data_index++) // STRUCT array FIXED
            {
                p_device_config->extra_data[extra_data_index].length = 2;

                for (int i = 0; i < 2; i++)
                {
                    p_device_config->extra_data[extra_data_index].data[i] = (UInt16)(i + 10);
                }
            }
        }
    }
    #endif /* idx9: extra_data E */

    /* idx10: band_count S */
    {
        p_device_config->band_count = 0;
    }
    /* idx10: band_count E */

    /* idx11: band_data S */
    {
        for (int band_data_index = 0; band_data_index < p_device_config->band_count; band_data_index++) // STRUCT array VARIABLE
        {
            p_device_config->band_data[band_data_index].bitmask = 0;
            p_device_config->band_data[band_data_index].band_id = 0;
            p_device_config->band_data[band_data_index].frequency = 0;
            p_device_config->band_data[band_data_index].optional_param_id = 0;
            p_device_config->band_data[band_data_index].optional_param_data = 0;
        }
    }
    /* idx11: band_data E */

    /* idx12: list_id S */
    {
        for (int list_id_index = 0; list_id_index < 80; list_id_index++) // array primitive FIXED
        {
            p_device_config->list_id[list_id_index] = (UInt8)(list_id_index & 0xFF);
        }
    }
    /* idx12: list_id E */

    /* idx13: plmn S */
    {
        /* idx14: plmn_count S */
        {
            p_device_config->plmn.plmn_count = 2;
        }
        /* idx14: plmn_count E */

        /* idx15: data S */
        {
            for (int data_index = 0; data_index < p_device_config->plmn.plmn_count; data_index++) // array primitive VARIABLE
            {
                p_device_config->plmn.data[data_index] = (UInt8)(data_index + 1);
            }
        }
        /* idx15: data E */
    }
    /* idx13: plmn E */

    return XNAP_SUCCESS;
}
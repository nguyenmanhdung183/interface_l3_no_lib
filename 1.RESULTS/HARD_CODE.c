
xnap_return_et assign_hardcode_value_device_config_t( device_config_t *p_device_config )
{
	    		p_device_config->bitmask = 0;
	    		p_device_config->version = 127;
	    			p_device_config->rf_params.bitmask = 0;
	    			p_device_config->rf_params.id = 500;
	    			p_device_config->rf_params.num_bands = 2;
	    				p_device_config->rf_params.bands[0].bitmask = 0;
	    				p_device_config->rf_params.bands[0].band_id = 1;
	    				p_device_config->rf_params.bands[0].frequency = 3000;
	
	    			#if 1 /*idx20: optional_param_id S */
	    				if (p_device_config->rf_params.bands[0].bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT)
	    				{
		    				p_device_config->rf_params.bands[0].optional_param_id = 5;
	    				}
	    			#endif /* idx20: optional_param_id E */
	
	
	    			#if 1 /*idx22: optional_param_data S */
	    				if (p_device_config->rf_params.bands[0].bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT)
	    				{
		    				p_device_config->rf_params.bands[0].optional_param_data = 127;
	    				}
	    			#endif /* idx22: optional_param_data E */
	
	    				p_device_config->rf_params.bands[1].bitmask = 0;
	    				p_device_config->rf_params.bands[1].band_id = 1;
	    				p_device_config->rf_params.bands[1].frequency = 3000;
	
	    			#if 1 /*idx30: optional_param_id S */
	    				if (p_device_config->rf_params.bands[1].bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT)
	    				{
		    				p_device_config->rf_params.bands[1].optional_param_id = 5;
	    				}
	    			#endif /* idx30: optional_param_id E */
	
	
	    			#if 1 /*idx32: optional_param_data S */
	    				if (p_device_config->rf_params.bands[1].bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT)
	    				{
		    				p_device_config->rf_params.bands[1].optional_param_data = 127;
	    				}
	    			#endif /* idx32: optional_param_data E */
	
	
	    		#if 1 /*idx34: config_blob S */
	    			if (p_device_config->rf_params.bitmask & RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT)
	    			{
		    				p_device_config->rf_params.config_blob[0].length_a = 2;
		    				/* p_device_config->rf_params.config_blob[0].data_a is an array primitive, assigning variale values */
	    				p_device_config->rf_params.config_blob[0].data_a = {0x01, 0x02}; /* example for octet string array */
		    				p_device_config->rf_params.config_blob[1].length_a = 2;
		    				/* p_device_config->rf_params.config_blob[1].data_a is an array primitive, assigning variale values */
	    				p_device_config->rf_params.config_blob[1].data_a = {0x01, 0x02}; /* example for octet string array */
	    			}
	    		#endif /* idx34: config_blob E */
	
	
	    	#if 1 /*idx44: extra_data_config S */
	    		if (p_device_config->bitmask & CONFIG_PRESENT)
	    		{
		    		p_device_config->extra_data_config = 0;
	    		}
	    	#endif /* idx44: extra_data_config E */
	
	
	    	#if 1 /*idx46: extra_data S */
	    		if (p_device_config->bitmask & DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT)
	    		{
		    			p_device_config->extra_data[0].length_a = 2;
		    			/* p_device_config->extra_data[0].data_a is an array primitive, assigning variale values */
	    			p_device_config->extra_data[0].data_a = {0x01, 0x02}; /* example for octet string array */
		    			p_device_config->extra_data[1].length_a = 2;
		    			/* p_device_config->extra_data[1].data_a is an array primitive, assigning variale values */
	    			p_device_config->extra_data[1].data_a = {0x01, 0x02}; /* example for octet string array */
	    		}
	    	#endif /* idx46: extra_data E */
	
	    		p_device_config->band_count = 2;
	    			p_device_config->band_data[0].bitmask = 0;
	    			p_device_config->band_data[0].band_id = 1;
	    			p_device_config->band_data[0].frequency = 3000;
	
	    		#if 1 /*idx66: optional_param_id S */
	    			if (p_device_config->band_data[0].bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT)
	    			{
		    			p_device_config->band_data[0].optional_param_id = 5;
	    			}
	    		#endif /* idx66: optional_param_id E */
	
	
	    		#if 1 /*idx68: optional_param_data S */
	    			if (p_device_config->band_data[0].bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT)
	    			{
		    			p_device_config->band_data[0].optional_param_data = 127;
	    			}
	    		#endif /* idx68: optional_param_data E */
	
	    			p_device_config->band_data[1].bitmask = 0;
	    			p_device_config->band_data[1].band_id = 1;
	    			p_device_config->band_data[1].frequency = 3000;
	
	    		#if 1 /*idx76: optional_param_id S */
	    			if (p_device_config->band_data[1].bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT)
	    			{
		    			p_device_config->band_data[1].optional_param_id = 5;
	    			}
	    		#endif /* idx76: optional_param_id E */
	
	
	    		#if 1 /*idx78: optional_param_data S */
	    			if (p_device_config->band_data[1].bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT)
	    			{
		    			p_device_config->band_data[1].optional_param_data = 127;
	    			}
	    		#endif /* idx78: optional_param_data E */
	
	    		/* p_device_config->list_id is an array primitive, assigning fixed values */
	    		p_device_config->list_id = {0x01, 0x02}; /* example for octet string array */
	    			p_device_config->plmn.plmn_count = 2;
	    			/* p_device_config->plmn.data is an array primitive, assigning variale values */
	    			p_device_config->plmn.data = {0x01, 0x02}; /* example for octet string array */
	    return XNAP_SUCCESS;
}

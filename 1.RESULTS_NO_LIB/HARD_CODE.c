
xnap_return_et assign_hardcode_value_device_config_t( device_config_t *p_device_config )
{
	    		p_device_config->bitmask = 0;
	    		p_device_config->version = 127;
	    			p_device_config->rf_params.bitmask = 0;
	    			p_device_config->rf_params.id = 500;

                    //memcpy(p_device_config->rf_params.nmd, (uint8_t[]){0x01,...}, 183); /* example for octet string array fixed */
	                for (int i = 0; i <  183; i++) {
		                    p_device_config->rf_params.nmd[i] = 0x01 + i; /* hardcode for fixed array */
	                }

	    			p_device_config->rf_params.num_bands = 2;
	    				p_device_config->rf_params.bands[0].bitmask = 0;
	    				p_device_config->rf_params.bands[0].band_id = 1;
	    				p_device_config->rf_params.bands[0].frequency = 3000;

	    			#if 1 /*idx22: optional_param_id S */
	    				p_device_config->rf_params.bands[0].bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT;
	    				p_device_config->rf_params.bands[0].optional_param_id = 5;
	    			#endif /* idx22: optional_param_id E */

	    			#if 1 /*idx24: optional_param_data S */
	    				p_device_config->rf_params.bands[0].bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT;
	    				p_device_config->rf_params.bands[0].optional_param_data = 127;
	    			#endif /* idx24: optional_param_data E */

                    //memcpy(p_device_config->rf_params.bands[0].NHL[0].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                    p_device_config->rf_params.bands[0].NHL[0].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }

	    					p_device_config->rf_params.bands[0].NHL[0].hihi = 0;

                    //memcpy(p_device_config->rf_params.bands[0].NHL[1].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                    p_device_config->rf_params.bands[0].NHL[1].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }

	    					p_device_config->rf_params.bands[0].NHL[1].hihi = 0;
	    				p_device_config->rf_params.bands[1].bitmask = 0;
	    				p_device_config->rf_params.bands[1].band_id = 1;
	    				p_device_config->rf_params.bands[1].frequency = 3000;

	    			#if 1 /*idx42: optional_param_id S */
	    				p_device_config->rf_params.bands[1].bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT;
	    				p_device_config->rf_params.bands[1].optional_param_id = 5;
	    			#endif /* idx42: optional_param_id E */

	    			#if 1 /*idx44: optional_param_data S */
	    				p_device_config->rf_params.bands[1].bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT;
	    				p_device_config->rf_params.bands[1].optional_param_data = 127;
	    			#endif /* idx44: optional_param_data E */

                    //memcpy(p_device_config->rf_params.bands[1].NHL[0].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                    p_device_config->rf_params.bands[1].NHL[0].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }

	    					p_device_config->rf_params.bands[1].NHL[0].hihi = 0;

                    //memcpy(p_device_config->rf_params.bands[1].NHL[1].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                    p_device_config->rf_params.bands[1].NHL[1].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }

	    					p_device_config->rf_params.bands[1].NHL[1].hihi = 0;

	    		#if 1 /*idx56: config_blob S */
	    			p_device_config->rf_params.bitmask |= RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT;
	    				p_device_config->rf_params.config_blob[0].length_a = 2;

                    //memcpy(p_device_config->rf_params.config_blob[0].data_a, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                for (int i = 0; i < p_device_config->rf_params.config_blob[0].length_a; i++) {
		                    p_device_config->rf_params.config_blob[0].data_a[i] = 0x01 + i; /* hardcode for variable array */
	                }

	    				p_device_config->rf_params.config_blob[1].length_a = 2;

                    //memcpy(p_device_config->rf_params.config_blob[1].data_a, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                for (int i = 0; i < p_device_config->rf_params.config_blob[1].length_a; i++) {
		                    p_device_config->rf_params.config_blob[1].data_a[i] = 0x01 + i; /* hardcode for variable array */
	                }

	    		#endif /* idx56: config_blob E */

	    	#if 1 /*idx66: extra_data_config S */
	    		p_device_config->bitmask |= CONFIG_PRESENT;
	    		p_device_config->extra_data_config = 0;
	    	#endif /* idx66: extra_data_config E */

	    	#if 1 /*idx68: extra_data S */
	    		p_device_config->bitmask |= DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT;
	    			p_device_config->extra_data[0].length_a = 2;

                    //memcpy(p_device_config->extra_data[0].data_a, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                for (int i = 0; i < p_device_config->extra_data[0].length_a; i++) {
		                    p_device_config->extra_data[0].data_a[i] = 0x01 + i; /* hardcode for variable array */
	                }

	    			p_device_config->extra_data[1].length_a = 2;

                    //memcpy(p_device_config->extra_data[1].data_a, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                for (int i = 0; i < p_device_config->extra_data[1].length_a; i++) {
		                    p_device_config->extra_data[1].data_a[i] = 0x01 + i; /* hardcode for variable array */
	                }

	    	#endif /* idx68: extra_data E */

	    		p_device_config->band_count = 2;
	    			p_device_config->band_data[0].bitmask = 0;
	    			p_device_config->band_data[0].band_id = 1;
	    			p_device_config->band_data[0].frequency = 3000;

	    		#if 1 /*idx88: optional_param_id S */
	    			p_device_config->band_data[0].bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT;
	    			p_device_config->band_data[0].optional_param_id = 5;
	    		#endif /* idx88: optional_param_id E */

	    		#if 1 /*idx90: optional_param_data S */
	    			p_device_config->band_data[0].bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT;
	    			p_device_config->band_data[0].optional_param_data = 127;
	    		#endif /* idx90: optional_param_data E */

                    //memcpy(p_device_config->band_data[0].NHL[0].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                    p_device_config->band_data[0].NHL[0].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }

	    				p_device_config->band_data[0].NHL[0].hihi = 0;

                    //memcpy(p_device_config->band_data[0].NHL[1].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                    p_device_config->band_data[0].NHL[1].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }

	    				p_device_config->band_data[0].NHL[1].hihi = 0;
	    			p_device_config->band_data[1].bitmask = 0;
	    			p_device_config->band_data[1].band_id = 1;
	    			p_device_config->band_data[1].frequency = 3000;

	    		#if 1 /*idx108: optional_param_id S */
	    			p_device_config->band_data[1].bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT;
	    			p_device_config->band_data[1].optional_param_id = 5;
	    		#endif /* idx108: optional_param_id E */

	    		#if 1 /*idx110: optional_param_data S */
	    			p_device_config->band_data[1].bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT;
	    			p_device_config->band_data[1].optional_param_data = 127;
	    		#endif /* idx110: optional_param_data E */

                    //memcpy(p_device_config->band_data[1].NHL[0].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                    p_device_config->band_data[1].NHL[0].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }

	    				p_device_config->band_data[1].NHL[0].hihi = 0;

                    //memcpy(p_device_config->band_data[1].NHL[1].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                    p_device_config->band_data[1].NHL[1].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }

	    				p_device_config->band_data[1].NHL[1].hihi = 0;

                    //memcpy(p_device_config->list_id, (uint8_t[]){0x01,...}, 80); /* example for octet string array fixed */
	                for (int i = 0; i <  80; i++) {
		                    p_device_config->list_id[i] = 0x01 + i; /* hardcode for fixed array */
	                }

	    			p_device_config->plmn.plmn_count = 2;

                    //memcpy(p_device_config->plmn.data, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                for (int i = 0; i < p_device_config->plmn.plmn_count; i++) {
		                    p_device_config->plmn.data[i] = 0x01 + i; /* hardcode for variable array */
	                }

	    return XNAP_SUCCESS;
}


xnap_return_et assign_hardcode_value_device_config_t( device_config_t *p_device_config )
{
	    		p_device_config->bitmask = 0;
	    		p_device_config->version = 127;
	    			p_device_config->rf_params.bitmask = 0;
	    			p_device_config->rf_params.id = 500;

	    			/*idx16 nmd S*/
    			//memcpy(p_device_config->rf_params.nmd, (uint8_t[]){0x01,...}, 183); /* example for octet string array fixed */
	                for (int i = 0; i <  183; i++) {
		                p_device_config->rf_params.nmd[i] = 0x01 + i; /* hardcode for fixed array */
	                }
	    			/*idx16 nmd E*/

	    			p_device_config->rf_params.num_bands = 2;
	    				p_device_config->rf_params.bands[0].present_bitmask = 0;
	    				p_device_config->rf_params.bands[0].band_id = 1;
	    				p_device_config->rf_params.bands[0].frequency = 3000;

	    			#if 1 /*idx31: optional_param_id S */
	    				p_device_config->rf_params.bands[0].present_bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT;
	    				p_device_config->rf_params.bands[0].optional_param_id = 5;
	    			#endif /* idx31: optional_param_id E */

	    			#if 1 /*idx34: optional_param_data S */
	    				p_device_config->rf_params.bands[0].present_bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT;
	    				p_device_config->rf_params.bands[0].optional_param_data = 127;
	    			#endif /* idx34: optional_param_data E */

	    					/*idx41 haha S*/
    					//memcpy(p_device_config->rf_params.bands[0].NHL[0].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                p_device_config->rf_params.bands[0].NHL[0].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }
	    					/*idx41 haha E*/

	    					p_device_config->rf_params.bands[0].NHL[0].hihi = 0;

	    					/*idx47 haha S*/
    					//memcpy(p_device_config->rf_params.bands[0].NHL[1].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                p_device_config->rf_params.bands[0].NHL[1].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }
	    					/*idx47 haha E*/

	    					p_device_config->rf_params.bands[0].NHL[1].hihi = 0;
	    					p_device_config->rf_params.bands[0].MD.numbits = 2;

	    					/*idx58 data S*/
    					//memcpy(p_device_config->rf_params.bands[0].MD.data, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                    for (int i = 0; i < p_device_config->rf_params.bands[0].MD.numbits/8; i++) {
		                    p_device_config->rf_params.bands[0].MD.data[i] = 0x01 + i; /* hardcode for variable array */
	                    }

	    					/*idx58 data E*/

	    				p_device_config->rf_params.bands[1].present_bitmask = 0;
	    				p_device_config->rf_params.bands[1].band_id = 1;
	    				p_device_config->rf_params.bands[1].frequency = 3000;

	    			#if 1 /*idx68: optional_param_id S */
	    				p_device_config->rf_params.bands[1].present_bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT;
	    				p_device_config->rf_params.bands[1].optional_param_id = 5;
	    			#endif /* idx68: optional_param_id E */

	    			#if 1 /*idx71: optional_param_data S */
	    				p_device_config->rf_params.bands[1].present_bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT;
	    				p_device_config->rf_params.bands[1].optional_param_data = 127;
	    			#endif /* idx71: optional_param_data E */

	    					/*idx78 haha S*/
    					//memcpy(p_device_config->rf_params.bands[1].NHL[0].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                p_device_config->rf_params.bands[1].NHL[0].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }
	    					/*idx78 haha E*/

	    					p_device_config->rf_params.bands[1].NHL[0].hihi = 0;

	    					/*idx84 haha S*/
    					//memcpy(p_device_config->rf_params.bands[1].NHL[1].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                p_device_config->rf_params.bands[1].NHL[1].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }
	    					/*idx84 haha E*/

	    					p_device_config->rf_params.bands[1].NHL[1].hihi = 0;
	    					p_device_config->rf_params.bands[1].MD.numbits = 2;

	    					/*idx95 data S*/
    					//memcpy(p_device_config->rf_params.bands[1].MD.data, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                    for (int i = 0; i < p_device_config->rf_params.bands[1].MD.numbits/8; i++) {
		                    p_device_config->rf_params.bands[1].MD.data[i] = 0x01 + i; /* hardcode for variable array */
	                    }

	    					/*idx95 data E*/

	    		#if 1 /*idx96: config_blob S */
	    			p_device_config->rf_params.bitmask |= RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT;
	    				p_device_config->rf_params.config_blob[0].length_a = 2;

	    				/*idx103 data_a S*/
    				//memcpy(p_device_config->rf_params.config_blob[0].data_a, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                    for (int i = 0; i < p_device_config->rf_params.config_blob[0].length_a; i++) {
		                    p_device_config->rf_params.config_blob[0].data_a[i] = 0x01 + i; /* hardcode for variable array */
	                    }

	    				/*idx103 data_a E*/

	    				p_device_config->rf_params.config_blob[1].length_a = 2;

	    				/*idx109 data_a S*/
    				//memcpy(p_device_config->rf_params.config_blob[1].data_a, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                    for (int i = 0; i < p_device_config->rf_params.config_blob[1].length_a; i++) {
		                    p_device_config->rf_params.config_blob[1].data_a[i] = 0x01 + i; /* hardcode for variable array */
	                    }

	    				/*idx109 data_a E*/

	    		#endif /* idx96: config_blob E */

	    	#if 1 /*idx110: extra_data_config S */
	    		p_device_config->bitmask |= CONFIG_PRESENT;
	    		p_device_config->extra_data_config = 0;
	    	#endif /* idx110: extra_data_config E */

	    	#if 1 /*idx113: extra_data S */
	    		p_device_config->bitmask |= DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT;
	    			p_device_config->extra_data[0].length_a = 2;

	    			/*idx120 data_a S*/
    			//memcpy(p_device_config->extra_data[0].data_a, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                    for (int i = 0; i < p_device_config->extra_data[0].length_a; i++) {
		                    p_device_config->extra_data[0].data_a[i] = 0x01 + i; /* hardcode for variable array */
	                    }

	    			/*idx120 data_a E*/

	    			p_device_config->extra_data[1].length_a = 2;

	    			/*idx126 data_a S*/
    			//memcpy(p_device_config->extra_data[1].data_a, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                    for (int i = 0; i < p_device_config->extra_data[1].length_a; i++) {
		                    p_device_config->extra_data[1].data_a[i] = 0x01 + i; /* hardcode for variable array */
	                    }

	    			/*idx126 data_a E*/

	    	#endif /* idx113: extra_data E */

	    		p_device_config->band_count = 2;
	    			p_device_config->band_data[0].present_bitmask = 0;
	    			p_device_config->band_data[0].band_id = 1;
	    			p_device_config->band_data[0].frequency = 3000;

	    		#if 1 /*idx141: optional_param_id S */
	    			p_device_config->band_data[0].present_bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT;
	    			p_device_config->band_data[0].optional_param_id = 5;
	    		#endif /* idx141: optional_param_id E */

	    		#if 1 /*idx144: optional_param_data S */
	    			p_device_config->band_data[0].present_bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT;
	    			p_device_config->band_data[0].optional_param_data = 127;
	    		#endif /* idx144: optional_param_data E */

	    				/*idx151 haha S*/
    				//memcpy(p_device_config->band_data[0].NHL[0].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                p_device_config->band_data[0].NHL[0].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }
	    				/*idx151 haha E*/

	    				p_device_config->band_data[0].NHL[0].hihi = 0;

	    				/*idx157 haha S*/
    				//memcpy(p_device_config->band_data[0].NHL[1].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                p_device_config->band_data[0].NHL[1].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }
	    				/*idx157 haha E*/

	    				p_device_config->band_data[0].NHL[1].hihi = 0;
	    				p_device_config->band_data[0].MD.numbits = 2;

	    				/*idx168 data S*/
    				//memcpy(p_device_config->band_data[0].MD.data, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                    for (int i = 0; i < p_device_config->band_data[0].MD.numbits/8; i++) {
		                    p_device_config->band_data[0].MD.data[i] = 0x01 + i; /* hardcode for variable array */
	                    }

	    				/*idx168 data E*/

	    			p_device_config->band_data[1].present_bitmask = 0;
	    			p_device_config->band_data[1].band_id = 1;
	    			p_device_config->band_data[1].frequency = 3000;

	    		#if 1 /*idx178: optional_param_id S */
	    			p_device_config->band_data[1].present_bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT;
	    			p_device_config->band_data[1].optional_param_id = 5;
	    		#endif /* idx178: optional_param_id E */

	    		#if 1 /*idx181: optional_param_data S */
	    			p_device_config->band_data[1].present_bitmask |= BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT;
	    			p_device_config->band_data[1].optional_param_data = 127;
	    		#endif /* idx181: optional_param_data E */

	    				/*idx188 haha S*/
    				//memcpy(p_device_config->band_data[1].NHL[0].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                p_device_config->band_data[1].NHL[0].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }
	    				/*idx188 haha E*/

	    				p_device_config->band_data[1].NHL[0].hihi = 0;

	    				/*idx194 haha S*/
    				//memcpy(p_device_config->band_data[1].NHL[1].haha, (uint8_t[]){0x01,...}, 10); /* example for octet string array fixed */
	                for (int i = 0; i <  10; i++) {
		                p_device_config->band_data[1].NHL[1].haha[i] = 0x01 + i; /* hardcode for fixed array */
	                }
	    				/*idx194 haha E*/

	    				p_device_config->band_data[1].NHL[1].hihi = 0;
	    				p_device_config->band_data[1].MD.numbits = 2;

	    				/*idx205 data S*/
    				//memcpy(p_device_config->band_data[1].MD.data, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                    for (int i = 0; i < p_device_config->band_data[1].MD.numbits/8; i++) {
		                    p_device_config->band_data[1].MD.data[i] = 0x01 + i; /* hardcode for variable array */
	                    }

	    				/*idx205 data E*/

	    		/*idx208 list_id S*/
    		//memcpy(p_device_config->list_id, (uint8_t[]){0x01,...}, 80); /* example for octet string array fixed */
	                for (int i = 0; i <  80; i++) {
		                p_device_config->list_id[i] = 0x01 + i; /* hardcode for fixed array */
	                }
	    		/*idx208 list_id E*/

	    			p_device_config->plmn.plmn_count = 2;

	    			/*idx216 data S*/
    			//memcpy(p_device_config->plmn.data, (uint8_t[]){0x01, 0x02}, 2); /* example for octet string array  */
	                    for (int i = 0; i < p_device_config->plmn.plmn_count; i++) {
		                    p_device_config->plmn.data[i] = 0x01 + i; /* hardcode for variable array */
	                    }

	    			/*idx216 data E*/

	    return XNAP_SUCCESS;
}

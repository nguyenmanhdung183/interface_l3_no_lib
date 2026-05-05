
void trace_device_config_t(device_config_t *p_device_config)
{
	    	fprintf(stderr, "\n[TRACE] ===== device_config_t =====\n");
	    	fprintf(stderr, "[TRACE] p_device_config->bitmask = %u\n", p_device_config->bitmask);
	    	fprintf(stderr, "[TRACE] p_device_config->version = %u\n", p_device_config->version);
	    	fprintf(stderr, "\n[TRACE] ===== rf_parameters_t =====\n");
	    	fprintf(stderr, "[TRACE] p_device_config->rf_params.bitmask = %u\n", p_device_config->rf_params.bitmask);
	    	fprintf(stderr, "[TRACE] p_device_config->rf_params.id = %u\n", p_device_config->rf_params.id);
	    	/* p_device_config->rf_params.nmd is an array primitive, fixed length */
	    	fprintf(stderr, "[TRACE -O-F] p_device_config->rf_params.nmd\n");
	    	for (int j1 = 0; j1 < 183; j1++)
	    	{
		    		fprintf(stderr, "p_device_config->rf_params.nmd[%d] = 0x%02X\n", j1, p_device_config->rf_params.nmd[j1]);
	    	}
	    	fprintf(stderr, "[TRACE] p_device_config->rf_params.num_bands = %u\n", p_device_config->rf_params.num_bands);
	    	for (int i1 = 0; i1 < p_device_config->rf_params.num_bands; i1++)
	    	{
		    		fprintf(stderr, "\n[TRACE] ===== band_parameters_t =====\n");
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].present_bitmask = %u\n", p_device_config->rf_params.bands[i1].present_bitmask);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].band_id = %u\n", p_device_config->rf_params.bands[i1].band_id);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].frequency = %u\n", p_device_config->rf_params.bands[i1].frequency);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].optional_param_id = %u\n", p_device_config->rf_params.bands[i1].optional_param_id);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].optional_param_data = %u\n", p_device_config->rf_params.bands[i1].optional_param_data);
		    		for (int i2 = 0; i2 < 2; i2++)
		    		{
			    			fprintf(stderr, "\n[TRACE] ===== dunglieu_t =====\n");
			    			/* p_device_config->rf_params.bands[i1].NHL[i2].haha is an array primitive, fixed length */
			    			fprintf(stderr, "[TRACE -O-F] p_device_config->rf_params.bands[i1].NHL[i2].haha\n");
			    			for (int j3 = 0; j3 < 10; j3++)
			    			{
				    				fprintf(stderr, "p_device_config->rf_params.bands[i1].NHL[i2].haha[%d] = 0x%02X\n", j3, p_device_config->rf_params.bands[i1].NHL[i2].haha[j3]);
			    			}
			    			fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].NHL[i2].hihi = %u\n", p_device_config->rf_params.bands[i1].NHL[i2].hihi);
		    		}
		    		fprintf(stderr, "\n[TRACE] ===== manhdung_t =====\n");
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].MD.numbits = %u\n", p_device_config->rf_params.bands[i1].MD.numbits);
		    		/* p_device_config->rf_params.bands[i1].MD.data is an array primitive, variable length in bits */
		    		fprintf(stderr, "[TRACE -O-V] p_device_config->rf_params.bands[i1].MD.data \n");
		    		for (int j2 = 0; j2 < p_device_config->rf_params.bands[i1].MD.numbits/8; j2++)
		    		{
			    			fprintf(stderr, "p_device_config->rf_params.bands[i1].MD.data[%d] = 0x%02X\n", j2, p_device_config->rf_params.bands[i1].MD.data[j2]);
		    		}
	    	}

	    	if (p_device_config->rf_params.bitmask & RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT)
	    	{
		    	for (int i1 = 0; i1 < 99; i1++)
		    	{
			    		fprintf(stderr, "\n[TRACE] ===== octet_string_t =====\n");
			    		fprintf(stderr, "[TRACE] p_device_config->rf_params.config_blob[i1].length_a = %u\n", p_device_config->rf_params.config_blob[i1].length_a);
			    		/* p_device_config->rf_params.config_blob[i1].data_a is an array primitive, variable length */
			    		fprintf(stderr, "[TRACE -O-V] p_device_config->rf_params.config_blob[i1].data_a \n");
			    		for (int j2 = 0; j2 < p_device_config->rf_params.config_blob[i1].length_a; j2++)
			    		{
				    			fprintf(stderr, "p_device_config->rf_params.config_blob[i1].data_a[%d] = 0x%02X\n", j2, p_device_config->rf_params.config_blob[i1].data_a[j2]);
			    		}
		    	}
	    	}
	    	fprintf(stderr, "[TRACE] p_device_config->extra_data_config = %u\n", p_device_config->extra_data_config);

	    	if (p_device_config->bitmask & DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT)
	    	{
		    	for (int i1 = 0; i1 < 20; i1++)
		    	{
			    		fprintf(stderr, "\n[TRACE] ===== octet_string_t =====\n");
			    		fprintf(stderr, "[TRACE] p_device_config->extra_data[i1].length_a = %u\n", p_device_config->extra_data[i1].length_a);
			    		/* p_device_config->extra_data[i1].data_a is an array primitive, variable length */
			    		fprintf(stderr, "[TRACE -O-V] p_device_config->extra_data[i1].data_a \n");
			    		for (int j2 = 0; j2 < p_device_config->extra_data[i1].length_a; j2++)
			    		{
				    			fprintf(stderr, "p_device_config->extra_data[i1].data_a[%d] = 0x%02X\n", j2, p_device_config->extra_data[i1].data_a[j2]);
			    		}
		    	}
	    	}
	    	fprintf(stderr, "[TRACE] p_device_config->band_count = %u\n", p_device_config->band_count);
	    	for (int i1 = 0; i1 < p_device_config->band_count; i1++)
	    	{
		    		fprintf(stderr, "\n[TRACE] ===== band_parameters_t =====\n");
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i1].present_bitmask = %u\n", p_device_config->band_data[i1].present_bitmask);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i1].band_id = %u\n", p_device_config->band_data[i1].band_id);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i1].frequency = %u\n", p_device_config->band_data[i1].frequency);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i1].optional_param_id = %u\n", p_device_config->band_data[i1].optional_param_id);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i1].optional_param_data = %u\n", p_device_config->band_data[i1].optional_param_data);
		    		for (int i2 = 0; i2 < 2; i2++)
		    		{
			    			fprintf(stderr, "\n[TRACE] ===== dunglieu_t =====\n");
			    			/* p_device_config->band_data[i1].NHL[i2].haha is an array primitive, fixed length */
			    			fprintf(stderr, "[TRACE -O-F] p_device_config->band_data[i1].NHL[i2].haha\n");
			    			for (int j3 = 0; j3 < 10; j3++)
			    			{
				    				fprintf(stderr, "p_device_config->band_data[i1].NHL[i2].haha[%d] = 0x%02X\n", j3, p_device_config->band_data[i1].NHL[i2].haha[j3]);
			    			}
			    			fprintf(stderr, "[TRACE] p_device_config->band_data[i1].NHL[i2].hihi = %u\n", p_device_config->band_data[i1].NHL[i2].hihi);
		    		}
		    		fprintf(stderr, "\n[TRACE] ===== manhdung_t =====\n");
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i1].MD.numbits = %u\n", p_device_config->band_data[i1].MD.numbits);
		    		/* p_device_config->band_data[i1].MD.data is an array primitive, variable length in bits */
		    		fprintf(stderr, "[TRACE -O-V] p_device_config->band_data[i1].MD.data \n");
		    		for (int j2 = 0; j2 < p_device_config->band_data[i1].MD.numbits/8; j2++)
		    		{
			    			fprintf(stderr, "p_device_config->band_data[i1].MD.data[%d] = 0x%02X\n", j2, p_device_config->band_data[i1].MD.data[j2]);
		    		}
	    	}
	    	/* p_device_config->list_id is an array primitive, fixed length */
	    	fprintf(stderr, "[TRACE -O-F] p_device_config->list_id\n");
	    	for (int j1 = 0; j1 < 80; j1++)
	    	{
		    		fprintf(stderr, "p_device_config->list_id[%d] = 0x%02X\n", j1, p_device_config->list_id[j1]);
	    	}
	    	fprintf(stderr, "\n[TRACE] ===== plmn_id_t =====\n");
	    	fprintf(stderr, "[TRACE] p_device_config->plmn.plmn_count = %u\n", p_device_config->plmn.plmn_count);
	    	/* p_device_config->plmn.data is an array primitive, variable length */
	    	fprintf(stderr, "[TRACE -O-V] p_device_config->plmn.data \n");
	    	for (int j1 = 0; j1 < p_device_config->plmn.plmn_count; j1++)
	    	{
		    		fprintf(stderr, "p_device_config->plmn.data[%d] = 0x%02X\n", j1, p_device_config->plmn.data[j1]);
	    	}
}

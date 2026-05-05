
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
	    	for (int j0 = 0; j0 < 183; j0++)
	    	{
		    		fprintf(stderr, "p_device_config->rf_params.nmd[%d] = 0x%02X\n", j0, p_device_config->rf_params.nmd[j0]);
	    	}
	    	fprintf(stderr, "[TRACE] p_device_config->rf_params.num_bands = %u\n", p_device_config->rf_params.num_bands);
	    	for (int i1 = 0; i1 < p_device_config->rf_params.num_bands; i1++)
	    	{
		    		fprintf(stderr, "\n[TRACE] ===== band_parameters_t =====\n");
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].bitmask = %u\n", p_device_config->rf_params.bands[i1].bitmask);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].band_id = %u\n", p_device_config->rf_params.bands[i1].band_id);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].frequency = %u\n", p_device_config->rf_params.bands[i1].frequency);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].optional_param_id = %u\n", p_device_config->rf_params.bands[i1].optional_param_id);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i1].optional_param_data = %u\n", p_device_config->rf_params.bands[i1].optional_param_data);
		    		for (int i2 = 0; i2 < 100; i2++)
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
	    	}

	    	if (p_device_config->rf_params.bitmask & RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT)
	    	{
		    	for (int i4 = 0; i4 < 99; i4++)
		    	{
			    		fprintf(stderr, "\n[TRACE] ===== octet_string_t =====\n");
			    		fprintf(stderr, "[TRACE] p_device_config->rf_params.config_blob[i4].length_a = %u\n", p_device_config->rf_params.config_blob[i4].length_a);
			    		/* p_device_config->rf_params.config_blob[i4].data_a is an array primitive, variable length */
			    		fprintf(stderr, "[TRACE -O-V] p_device_config->rf_params.config_blob[i4].data_a \n");
			    		for (int j5 = 0; j5 < p_device_config->rf_params.config_blob[i4].length_a; j5++)
			    		{
				    			fprintf(stderr, "p_device_config->rf_params.config_blob[i4].data_a[%d] = 0x%02X\n", j5, p_device_config->rf_params.config_blob[i4].data_a[j5]);
			    		}
		    	}
	    	}
	    	fprintf(stderr, "[TRACE] p_device_config->extra_data_config = %u\n", p_device_config->extra_data_config);

	    	if (p_device_config->bitmask & DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT)
	    	{
		    	for (int i6 = 0; i6 < 20; i6++)
		    	{
			    		fprintf(stderr, "\n[TRACE] ===== octet_string_t =====\n");
			    		fprintf(stderr, "[TRACE] p_device_config->extra_data[i6].length_a = %u\n", p_device_config->extra_data[i6].length_a);
			    		/* p_device_config->extra_data[i6].data_a is an array primitive, variable length */
			    		fprintf(stderr, "[TRACE -O-V] p_device_config->extra_data[i6].data_a \n");
			    		for (int j7 = 0; j7 < p_device_config->extra_data[i6].length_a; j7++)
			    		{
				    			fprintf(stderr, "p_device_config->extra_data[i6].data_a[%d] = 0x%02X\n", j7, p_device_config->extra_data[i6].data_a[j7]);
			    		}
		    	}
	    	}
	    	fprintf(stderr, "[TRACE] p_device_config->band_count = %u\n", p_device_config->band_count);
	    	for (int i8 = 0; i8 < p_device_config->band_count; i8++)
	    	{
		    		fprintf(stderr, "\n[TRACE] ===== band_parameters_t =====\n");
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i8].bitmask = %u\n", p_device_config->band_data[i8].bitmask);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i8].band_id = %u\n", p_device_config->band_data[i8].band_id);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i8].frequency = %u\n", p_device_config->band_data[i8].frequency);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i8].optional_param_id = %u\n", p_device_config->band_data[i8].optional_param_id);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i8].optional_param_data = %u\n", p_device_config->band_data[i8].optional_param_data);
		    		for (int i9 = 0; i9 < 100; i9++)
		    		{
			    			fprintf(stderr, "\n[TRACE] ===== dunglieu_t =====\n");
			    			/* p_device_config->band_data[i8].NHL[i9].haha is an array primitive, fixed length */
			    			fprintf(stderr, "[TRACE -O-F] p_device_config->band_data[i8].NHL[i9].haha\n");
			    			for (int j10 = 0; j10 < 10; j10++)
			    			{
				    				fprintf(stderr, "p_device_config->band_data[i8].NHL[i9].haha[%d] = 0x%02X\n", j10, p_device_config->band_data[i8].NHL[i9].haha[j10]);
			    			}
			    			fprintf(stderr, "[TRACE] p_device_config->band_data[i8].NHL[i9].hihi = %u\n", p_device_config->band_data[i8].NHL[i9].hihi);
		    		}
	    	}
	    	/* p_device_config->list_id is an array primitive, fixed length */
	    	fprintf(stderr, "[TRACE -O-F] p_device_config->list_id\n");
	    	for (int j11 = 0; j11 < 80; j11++)
	    	{
		    		fprintf(stderr, "p_device_config->list_id[%d] = 0x%02X\n", j11, p_device_config->list_id[j11]);
	    	}
	    	fprintf(stderr, "\n[TRACE] ===== plmn_id_t =====\n");
	    	fprintf(stderr, "[TRACE] p_device_config->plmn.plmn_count = %u\n", p_device_config->plmn.plmn_count);
	    	/* p_device_config->plmn.data is an array primitive, variable length */
	    	fprintf(stderr, "[TRACE -O-V] p_device_config->plmn.data \n");
	    	for (int j12 = 0; j12 < p_device_config->plmn.plmn_count; j12++)
	    	{
		    		fprintf(stderr, "p_device_config->plmn.data[%d] = 0x%02X\n", j12, p_device_config->plmn.data[j12]);
	    	}
}

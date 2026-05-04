
#include <stdio.h>

void trace_device_config_t(device_config_t *p_device_config)
{
	    	fprintf(stderr, "\n[TRACE] ===== device_config_t =====\n");
	    	fprintf(stderr, "[TRACE] p_device_config->bitmask = %u\n", p_device_config->bitmask);
	    	fprintf(stderr, "[TRACE] p_device_config->version = %u\n", p_device_config->version);
	    	fprintf(stderr, "\n[TRACE] ===== rf_parameters_t =====\n");
	    	fprintf(stderr, "[TRACE] p_device_config->rf_params.bitmask = %u\n", p_device_config->rf_params.bitmask);
	    	fprintf(stderr, "[TRACE] p_device_config->rf_params.id = %u\n", p_device_config->rf_params.id);
	    	fprintf(stderr, "[TRACE] p_device_config->rf_params.num_bands = %u\n", p_device_config->rf_params.num_bands);
	    	for (int i = 0; i < MAX_BANDS; i++)
	    	{
		    		fprintf(stderr, "\n[TRACE] ===== band_parameters_t =====\n");
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i].bitmask = %u\n", p_device_config->rf_params.bands[i].bitmask);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i].band_id = %u\n", p_device_config->rf_params.bands[i].band_id);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i].frequency = %u\n", p_device_config->rf_params.bands[i].frequency);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i].optional_param_id = %u\n", p_device_config->rf_params.bands[i].optional_param_id);
		    		fprintf(stderr, "[TRACE] p_device_config->rf_params.bands[i].optional_param_data = %u\n", p_device_config->rf_params.bands[i].optional_param_data);
	    	}
	
	    	if (p_device_config->rf_params.bitmask & RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT)
	    	{
		    	for (int i = 0; i < 100; i++)
		    	{
			    		fprintf(stderr, "\n[TRACE] ===== octet_string_t =====\n");
			    		fprintf(stderr, "[TRACE] p_device_config->rf_params.config_blob[i].length_a = %u\n", p_device_config->rf_params.config_blob[i].length_a);
			    		/* p_device_config->rf_params.config_blob[i].data_a is an array primitive, variable length */
			    		for (int i = 0; i < p_device_config->rf_params.config_blob[i].data_a; i++)
			    		{
				    			fprintf(stderr, "[TRACE] p_device_config->rf_params.config_blob[i].data_a[%d] = 0x%02X\n", i, p_device_config->rf_params.config_blob[i].data_a.data[i]);
			    		}
		    	}
	    	}
	    	fprintf(stderr, "[TRACE] p_device_config->extra_data_config = %u\n", p_device_config->extra_data_config);
	
	    	if (p_device_config->bitmask & DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT)
	    	{
		    	for (int i = 0; i < 20; i++)
		    	{
			    		fprintf(stderr, "\n[TRACE] ===== octet_string_t =====\n");
			    		fprintf(stderr, "[TRACE] p_device_config->extra_data[i].length_a = %u\n", p_device_config->extra_data[i].length_a);
			    		/* p_device_config->extra_data[i].data_a is an array primitive, variable length */
			    		for (int i = 0; i < p_device_config->extra_data[i].data_a; i++)
			    		{
				    			fprintf(stderr, "[TRACE] p_device_config->extra_data[i].data_a[%d] = 0x%02X\n", i, p_device_config->extra_data[i].data_a.data[i]);
			    		}
		    	}
	    	}
	    	fprintf(stderr, "[TRACE] p_device_config->band_count = %u\n", p_device_config->band_count);
	    	for (int i = 0; i < 100; i++)
	    	{
		    		fprintf(stderr, "\n[TRACE] ===== band_parameters_t =====\n");
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i].bitmask = %u\n", p_device_config->band_data[i].bitmask);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i].band_id = %u\n", p_device_config->band_data[i].band_id);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i].frequency = %u\n", p_device_config->band_data[i].frequency);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i].optional_param_id = %u\n", p_device_config->band_data[i].optional_param_id);
		    		fprintf(stderr, "[TRACE] p_device_config->band_data[i].optional_param_data = %u\n", p_device_config->band_data[i].optional_param_data);
	    	}
	    	/* p_device_config->list_id is an array primitive, fixed length */
	    	for (int i = 0; i < p_device_config->list_id.; i++)
	    	{
		    		fprintf(stderr, "[TRACE] p_device_config->list_id.[%d] = 0x%02X\n", i, p_device_config->list_id.data[i]);
	    	}
	    	fprintf(stderr, "\n[TRACE] ===== plmn_id_t =====\n");
	    	fprintf(stderr, "[TRACE] p_device_config->plmn.plmn_count = %u\n", p_device_config->plmn.plmn_count);
	    	/* p_device_config->plmn.data is an array primitive, variable length */
	    	for (int i = 0; i < p_device_config->plmn.data; i++)
	    	{
		    		fprintf(stderr, "[TRACE] p_device_config->plmn.data[%d] = 0x%02X\n", i, p_device_config->plmn.data.data[i]);
	    	}
}

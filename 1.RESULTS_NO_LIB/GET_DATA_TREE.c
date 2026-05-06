
/* helper start */

static void trace_indent(int level)
{
	    for (int i = 0; i < level; i++)
	    {
		        fprintf(stderr, "│   ");
	    }
}

static void trace_node(int level, const char *name)
{
	    trace_indent(level);
	    fprintf(stderr, "%s\n", name);
}

static void trace_field_u32(int level, const char *name, unsigned int val)
{
	    trace_indent(level);
	    fprintf(stderr, "├── %s = %u\n", name, val);
}

static void trace_field_hex(int level, const char *name, unsigned char val)
{
	    trace_indent(level);
	    fprintf(stderr, "├── %s = 0x%02X\n", name, val);
}

/* helper end */

void trace_device_config_t_tree(device_config_t *p_device_config)
{
	    trace_node(0, "device_config_t");
	    	trace_field_u32(1, "bitmask", p_device_config->bitmask);
	    	trace_field_u32(1, "version", p_device_config->version);
	    	trace_indent(1);
	    	fprintf(stderr, "├── rf_params : rf_parameters_t\n");
	    		trace_field_u32(2, "bitmask", p_device_config->rf_params.bitmask);
	    		trace_field_u32(2, "id", p_device_config->rf_params.id);
	    		trace_indent(2);
	    		fprintf(stderr, "├── nmd[]\n");
	    		for (int i = 0; i < 183; i++)
	    		{
		    			trace_indent(3);
		    			fprintf(stderr, "├── nmd[%d] = 0x%02X\n", i, p_device_config->rf_params.nmd[i]);
	    		}
	    		trace_field_u32(2, "num_bands", p_device_config->rf_params.num_bands);
	    		trace_indent(2);
	    		fprintf(stderr, "├── bands : band_parameters_t\n");
	    		for (int i = 0; i < MAX_BANDS; i++)
	    		{
		    			trace_indent(3);
		    			fprintf(stderr, "├── bands[%d]\n", i);
		    				trace_field_u32(4, "present_bitmask", p_device_config->rf_params.bands[i].present_bitmask);
		    				trace_field_u32(4, "band_id", p_device_config->rf_params.bands[i].band_id);
		    				trace_field_u32(4, "frequency", p_device_config->rf_params.bands[i].frequency);
		    				trace_field_u32(4, "optional_param_id", p_device_config->rf_params.bands[i].optional_param_id);
		    				trace_field_u32(4, "optional_param_data", p_device_config->rf_params.bands[i].optional_param_data);
		    				trace_indent(4);
		    				fprintf(stderr, "├── NHL : dunglieu_t\n");
		    				for (int i = 0; i < 2; i++)
		    				{
			    					trace_indent(5);
			    					fprintf(stderr, "├── NHL[%d]\n", i);
			    						trace_indent(6);
			    						fprintf(stderr, "├── haha[]\n");
			    						for (int i = 0; i < 10; i++)
			    						{
				    							trace_indent(7);
				    							fprintf(stderr, "├── haha[%d] = 0x%02X\n", i, p_device_config->rf_params.bands[i].NHL[i].haha[i]);
			    						}
			    						trace_field_u32(6, "hihi", p_device_config->rf_params.bands[i].NHL[i].hihi);
		    				}
		    				trace_indent(4);
		    				fprintf(stderr, "├── MD : manhdung_t\n");
		    					trace_field_u32(5, "numbits", p_device_config->rf_params.bands[i].MD.numbits);
		    					trace_indent(5);
		    					fprintf(stderr, "├── data[]\n");
		    					for (int i = 0; i < 5; i++)
		    					{
			    						trace_indent(6);
			    						fprintf(stderr, "├── data[%d] = 0x%02X\n", i, p_device_config->rf_params.bands[i].MD.data[i]);
		    					}
	    		}
	    		trace_indent(2);
	    		fprintf(stderr, "├── config_blob : octet_string_t\n");
	    		for (int i = 0; i < 99; i++)
	    		{
		    			trace_indent(3);
		    			fprintf(stderr, "├── config_blob[%d]\n", i);
		    				trace_field_u32(4, "length_a", p_device_config->rf_params.config_blob[i].length_a);
		    				trace_indent(4);
		    				fprintf(stderr, "├── data_a[]\n");
		    				for (int i = 0; i < MAX_OCTET_STRING_LEN; i++)
		    				{
			    					trace_indent(5);
			    					fprintf(stderr, "├── data_a[%d] = 0x%02X\n", i, p_device_config->rf_params.config_blob[i].data_a[i]);
		    				}
	    		}
	    	trace_field_u32(1, "extra_data_config", p_device_config->extra_data_config);
	    	trace_indent(1);
	    	fprintf(stderr, "├── extra_data : octet_string_t\n");
	    	for (int i = 0; i < 20; i++)
	    	{
		    		trace_indent(2);
		    		fprintf(stderr, "├── extra_data[%d]\n", i);
		    			trace_field_u32(3, "length_a", p_device_config->extra_data[i].length_a);
		    			trace_indent(3);
		    			fprintf(stderr, "├── data_a[]\n");
		    			for (int i = 0; i < MAX_OCTET_STRING_LEN; i++)
		    			{
			    				trace_indent(4);
			    				fprintf(stderr, "├── data_a[%d] = 0x%02X\n", i, p_device_config->extra_data[i].data_a[i]);
		    			}
	    	}
	    	trace_field_u32(1, "band_count", p_device_config->band_count);
	    	trace_indent(1);
	    	fprintf(stderr, "├── band_data : band_parameters_t\n");
	    	for (int i = 0; i < 100; i++)
	    	{
		    		trace_indent(2);
		    		fprintf(stderr, "├── band_data[%d]\n", i);
		    			trace_field_u32(3, "present_bitmask", p_device_config->band_data[i].present_bitmask);
		    			trace_field_u32(3, "band_id", p_device_config->band_data[i].band_id);
		    			trace_field_u32(3, "frequency", p_device_config->band_data[i].frequency);
		    			trace_field_u32(3, "optional_param_id", p_device_config->band_data[i].optional_param_id);
		    			trace_field_u32(3, "optional_param_data", p_device_config->band_data[i].optional_param_data);
		    			trace_indent(3);
		    			fprintf(stderr, "├── NHL : dunglieu_t\n");
		    			for (int i = 0; i < 2; i++)
		    			{
			    				trace_indent(4);
			    				fprintf(stderr, "├── NHL[%d]\n", i);
			    					trace_indent(5);
			    					fprintf(stderr, "├── haha[]\n");
			    					for (int i = 0; i < 10; i++)
			    					{
				    						trace_indent(6);
				    						fprintf(stderr, "├── haha[%d] = 0x%02X\n", i, p_device_config->band_data[i].NHL[i].haha[i]);
			    					}
			    					trace_field_u32(5, "hihi", p_device_config->band_data[i].NHL[i].hihi);
		    			}
		    			trace_indent(3);
		    			fprintf(stderr, "├── MD : manhdung_t\n");
		    				trace_field_u32(4, "numbits", p_device_config->band_data[i].MD.numbits);
		    				trace_indent(4);
		    				fprintf(stderr, "├── data[]\n");
		    				for (int i = 0; i < 5; i++)
		    				{
			    					trace_indent(5);
			    					fprintf(stderr, "├── data[%d] = 0x%02X\n", i, p_device_config->band_data[i].MD.data[i]);
		    				}
	    	}
	    	trace_indent(1);
	    	fprintf(stderr, "├── list_id[]\n");
	    	for (int i = 0; i < 80; i++)
	    	{
		    		trace_indent(2);
		    		fprintf(stderr, "├── list_id[%d] = 0x%02X\n", i, p_device_config->list_id[i]);
	    	}
	    	trace_indent(1);
	    	fprintf(stderr, "├── plmn : plmn_id_t\n");
	    		trace_field_u32(2, "plmn_count", p_device_config->plmn.plmn_count);
	    		trace_indent(2);
	    		fprintf(stderr, "├── data[]\n");
	    		for (int i = 0; i < MAX_OCTET_STRING_LEN; i++)
	    		{
		    			trace_indent(3);
		    			fprintf(stderr, "├── data[%d] = 0x%02X\n", i, p_device_config->plmn.data[i]);
	    		}
	    	trace_indent(1);
	    	fprintf(stderr, "├── test_print : TEST_PRINT\n");
	    		trace_field_u32(2, "data", p_device_config->test_print.data);
}

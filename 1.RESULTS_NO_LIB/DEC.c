static
gnb_return_et
gnb_il_parse_band_parameters
(
    band_parameters_t * p_band_parameters,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
){
	    SInt32 length_read = 0;
	    *p_length_read = 0;

	    memset(p_band_parameters, 0, sizeof(band_parameters_t));

	    /* This function parses band_parameters */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing band_parameters");

	/*----> rrc_bitmask_t ~ bitmask <----*/ 

	    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt16(&p_band_parameters->bitmask, p_src + *p_length_read, "bitmask");
	    *p_length_read += sizeof(p_band_parameters->bitmask);

	/*----> UInt8 ~ band_id <----*/ 

	    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt8(&p_band_parameters->band_id, p_src + *p_length_read, "band_id");
	    *p_length_read += sizeof(p_band_parameters->band_id);

	    /* Check for correct range [H - higher boundary] */
	    if(p_band_parameters->band_id > 3)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->band_id should be less than or equal to 3"
		            "Incorrect value: %d", p_band_parameters->band_id);
		        return GNB_FAILURE;

	    }

	/*----> UInt16 ~ frequency <----*/ 

	    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt16(&p_band_parameters->frequency, p_src + *p_length_read, "frequency");
	    *p_length_read += sizeof(p_band_parameters->frequency);

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_band_parameters->frequency < 0 || p_band_parameters->frequency > 6000) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->frequency should be in range [ 0 - 6000]"
		            "Incorrect value: %d", p_band_parameters->frequency);
		        return GNB_FAILURE;

	    }

	/*----> UInt8 ~ optional_param_id <----*/ 

	    /* Optional element */
	    if(p_band_parameters->bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT)
	    {

		    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
		    {
			        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
			        return GNB_FAILURE;
		    }
		    /* Parse/Unpack parameter of basic type */
		    gnb_cp_unpack_UInt8(&p_band_parameters->optional_param_id, p_src + *p_length_read, "optional_param_id");
		    *p_length_read += sizeof(p_band_parameters->optional_param_id);

		    /* Check for correct range [H - higher boundary] */
		    if(p_band_parameters->optional_param_id > 10)
		    {
			        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->optional_param_id should be less than or equal to 10"
			            "Incorrect value: %d", p_band_parameters->optional_param_id);
			        return GNB_FAILURE;

		    }

	    }

	/*----> UInt8 ~ optional_param_data <----*/ 

	    /* Optional element */
	    if(p_band_parameters->bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT)
	    {

		    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
		    {
			        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
			        return GNB_FAILURE;
		    }
		    /* Parse/Unpack parameter of basic type */
		    gnb_cp_unpack_UInt8(&p_band_parameters->optional_param_data, p_src + *p_length_read, "optional_param_data");
		    *p_length_read += sizeof(p_band_parameters->optional_param_data);

		    /* Check for correct range [B - both higher and lower boundary] */
		    if(p_band_parameters->optional_param_data < 0 || p_band_parameters->optional_param_data > 255) 
		    {
			        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->optional_param_data should be in range [ 0 - 255]"
			            "Incorrect value: %d", p_band_parameters->optional_param_data);
			        return GNB_FAILURE;

		    }

	    }

	/* final check */
	    if(*p_length_read > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }

	    return GNG_SUCCESS;
}

static
gnb_return_et
gnb_il_parse_plmn_id
(
    plmn_id_t * p_plmn_id,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
){
	    SInt32 length_read = 0;
	    *p_length_read = 0;

	    memset(p_plmn_id, 0, sizeof(plmn_id_t));

	    /* This function parses plmn_id */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing plmn_id");

	/*----> UInt8 ~ plmn_count <----*/ 

	    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt8(&p_plmn_id->plmn_count, p_src + *p_length_read, "plmn_count");
	    *p_length_read += sizeof(p_plmn_id->plmn_count);

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_plmn_id->plmn_count < 0 || p_plmn_id->plmn_count > MAX_OCTET_STRING_LEN) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_plmn_id->plmn_count should be in range [ 0 - MAX_OCTET_STRING_LEN]"
		            "Incorrect value: %d", p_plmn_id->plmn_count);
		        return GNB_FAILURE;

	    }

	/*----> UInt8 ~ data <----*/ 

	    /* Parse OCTET_STRING VARIABLE of basic type elements */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < p_plmn_id->plmn_count; loop++)
		        {
			            gnb_cp_unpack_UInt8((void*)(&p_plmn_id->data[loop]), (void*)(p_src + *p_length_read), "data[]");
			            *p_length_read += sizeof(UInt8);
		        }
	    }

	/* final check */
	    if(*p_length_read > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }

	    return GNG_SUCCESS;
}

static
gnb_return_et
gnb_il_parse_octet_string
(
    octet_string_t * p_octet_string,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
){
	    SInt32 length_read = 0;
	    *p_length_read = 0;

	    memset(p_octet_string, 0, sizeof(octet_string_t));

	    /* This function parses octet_string */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing octet_string");

	/*----> UInt8 ~ length_a <----*/ 

	    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt8(&p_octet_string->length_a, p_src + *p_length_read, "length_a");
	    *p_length_read += sizeof(p_octet_string->length_a);

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_octet_string->length_a < 0 || p_octet_string->length_a > MAX_OCTET_STRING_LEN) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_octet_string->length_a should be in range [ 0 - MAX_OCTET_STRING_LEN]"
		            "Incorrect value: %d", p_octet_string->length_a);
		        return GNB_FAILURE;

	    }

	/*----> UInt16 ~ data_a <----*/ 

	    /* Parse OCTET_STRING VARIABLE of basic type elements */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < p_octet_string->length_a; loop++)
		        {
			            gnb_cp_unpack_UInt16((void*)(&p_octet_string->data_a[loop]), (void*)(p_src + *p_length_read), "data_a[]");
			            *p_length_read += sizeof(UInt16);
		        }
	    }

	/* final check */
	    if(*p_length_read > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }

	    return GNG_SUCCESS;
}

static
gnb_return_et
gnb_il_parse_rf_parameters
(
    rf_parameters_t * p_rf_parameters,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
){
	    SInt32 length_read = 0;
	    *p_length_read = 0;

	    memset(p_rf_parameters, 0, sizeof(rf_parameters_t));

	    /* This function parses rf_parameters */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing rf_parameters");

	/*----> rrc_bitmask_t ~ bitmask <----*/ 

	    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt16(&p_rf_parameters->bitmask, p_src + *p_length_read, "bitmask");
	    *p_length_read += sizeof(p_rf_parameters->bitmask);

	/*----> UInt16 ~ id <----*/ 

	    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt16(&p_rf_parameters->id, p_src + *p_length_read, "id");
	    *p_length_read += sizeof(p_rf_parameters->id);

	/*----> UInt8 ~ nmd <----*/ 

	    /* Parse of OCTET_STRING FIXED of basic type elements */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < ARRSIZE(p_rf_parameters->nmd); loop++)
		        {
			            gnb_cp_unpack_UInt8((void*)(&p_rf_parameters->nmd[loop]), (void*)(p_src + *p_length_read), "nmd[]");
			            *p_length_read += sizeof(UInt8);
		        }
	    }

	/*----> UInt8 ~ num_bands <----*/ 

	    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt8(&p_rf_parameters->num_bands, p_src + *p_length_read, "num_bands");
	    *p_length_read += sizeof(p_rf_parameters->num_bands);

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_rf_parameters->num_bands < 0 || p_rf_parameters->num_bands > MAX_BANDS) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_rf_parameters->num_bands should be in range [ 0 - MAX_BANDS]"
		            "Incorrect value: %d", p_rf_parameters->num_bands);
		        return GNB_FAILURE;

	    }

	/*----> band_parameters_t ~ bands <----*/ 

	    /* Parse OCTET_STRING VARIABLE of IE */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < p_rf_parameters->num_bands; loop++)
		        {
			            if(GNB_FAILURE == gnb_il_parse_band_parameters(
			                &p_rf_parameters->bands[loop], 
			                p_src + *p_length_read, 
			                length_left - *p_length_read,
			                &length_read))
			            {
				                return GNB_FAILURE;
			            }
			            *p_length_read += length_read;
		        }
	    }

	/*----> octet_string_t ~ config_blob <----*/ 

	    /* Optional element */
	    if(p_rf_parameters->bitmask & RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT)
	    {

		    /* Parse of OCTET_STRING FIXED of IEs */
		    {
			        //:))))
			        gnb_counter_t loop;
			        for(loop = 0; loop < ARRSIZE(p_rf_parameters->config_blob); loop++)
			        {
				            if(GNB_FAILURE == gnb_il_parse_octet_string(
				                &p_rf_parameters->config_blob[loop], 
				                p_src + *p_length_read, 
				                length_left - *p_length_read,
				                &length_read))
				            {
					                return GNB_FAILURE;
				            }
				            *p_length_read += length_read;
			        }
		    }

	    }

	/* final check */
	    if(*p_length_read > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }

	    return GNG_SUCCESS;
}

static
gnb_return_et
gnb_il_parse_device_config
(
    device_config_t * p_device_config,
    UInt8 * p_src,
    SInt32 length_left,
    SInt32 * p_length_read
){
	    SInt32 length_read = 0;
	    *p_length_read = 0;

	    memset(p_device_config, 0, sizeof(device_config_t));

	    /* This function parses device_config */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Parsing device_config");

	/*----> UInt16 ~ bitmask <----*/ 

	    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt16(&p_device_config->bitmask, p_src + *p_length_read, "bitmask");
	    *p_length_read += sizeof(p_device_config->bitmask);

	/*----> UInt8 ~ version <----*/ 

	    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt8(&p_device_config->version, p_src + *p_length_read, "version");
	    *p_length_read += sizeof(p_device_config->version);

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_device_config->version < 0 || p_device_config->version > 255) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_device_config->version should be in range [ 0 - 255]"
		            "Incorrect value: %d", p_device_config->version);
		        return GNB_FAILURE;

	    }

	/*----> rf_parameters_t ~ rf_params <----*/ 

	    /* Parse/Unpack IE */
	    if(GNB_FAILURE == gnb_il_parse_rf_parameters(
	        &p_device_config->rf_params, 
	        p_src + *p_length_read, 
	        length_left - *p_length_read,
	        &length_read))
	    {
		        return GNB_FAILURE;
	    }

	    *p_length_read += length_read;

	/*----> UInt8 ~ extra_data_config <----*/ 

	    /* Optional element */
	    if(p_device_config->bitmask & CONFIG_PRESENT)
	    {

		    if (*p_length_read + (SInt32)sizeof(UInt8) > length_left)
		    {
			        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
			        return GNB_FAILURE;
		    }
		    /* Parse/Unpack parameter of basic type */
		    gnb_cp_unpack_UInt8(&p_device_config->extra_data_config, p_src + *p_length_read, "extra_data_config");
		    *p_length_read += sizeof(p_device_config->extra_data_config);

	    }

	/*----> octet_string_t ~ extra_data <----*/ 

	    /* Optional element */
	    if(p_device_config->bitmask & DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT)
	    {

		    /* Parse of OCTET_STRING FIXED of IEs */
		    {
			        //:))))
			        gnb_counter_t loop;
			        for(loop = 0; loop < ARRSIZE(p_device_config->extra_data); loop++)
			        {
				            if(GNB_FAILURE == gnb_il_parse_octet_string(
				                &p_device_config->extra_data[loop], 
				                p_src + *p_length_read, 
				                length_left - *p_length_read,
				                &length_read))
				            {
					                return GNB_FAILURE;
				            }
				            *p_length_read += length_read;
			        }
		    }

	    }

	/*----> UInt16 ~ band_count <----*/ 

	    if (*p_length_read + (SInt32)sizeof(UInt16) > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }
	    /* Parse/Unpack parameter of basic type */
	    gnb_cp_unpack_UInt16(&p_device_config->band_count, p_src + *p_length_read, "band_count");
	    *p_length_read += sizeof(p_device_config->band_count);

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_device_config->band_count < 0 || p_device_config->band_count > MAX_COUNT) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_device_config->band_count should be in range [ 0 - MAX_COUNT]"
		            "Incorrect value: %d", p_device_config->band_count);
		        return GNB_FAILURE;

	    }

	/*----> band_parameters_t ~ band_data <----*/ 

	    /* Parse OCTET_STRING VARIABLE of IE */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < p_device_config->band_count; loop++)
		        {
			            if(GNB_FAILURE == gnb_il_parse_band_parameters(
			                &p_device_config->band_data[loop], 
			                p_src + *p_length_read, 
			                length_left - *p_length_read,
			                &length_read))
			            {
				                return GNB_FAILURE;
			            }
			            *p_length_read += length_read;
		        }
	    }

	/*----> UInt8 ~ list_id <----*/ 

	    /* Parse of OCTET_STRING FIXED of basic type elements */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < ARRSIZE(p_device_config->list_id); loop++)
		        {
			            gnb_cp_unpack_UInt8((void*)(&p_device_config->list_id[loop]), (void*)(p_src + *p_length_read), "list_id[]");
			            *p_length_read += sizeof(UInt8);
		        }
	    }

	/*----> plmn_id_t ~ plmn <----*/ 

	    /* Parse/Unpack IE */
	    if(GNB_FAILURE == gnb_il_parse_plmn_id(
	        &p_device_config->plmn, 
	        p_src + *p_length_read, 
	        length_left - *p_length_read,
	        &length_read))
	    {
		        return GNB_FAILURE;
	    }

	    *p_length_read += length_read;

	/* final check */
	    if(*p_length_read > length_left)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Incomming message damaged!");
		        return GNB_FAILURE;
	    }

	    return GNG_SUCCESS;
}

/* get length */
static
gnb_length_t
gnb_il_get_octet_string_len 
(
    octet_string_t * p_octet_string
){
	    gnb_length_t length = 0;
	    GNB_ASSERT(p_octet_string != GNB_P_NULL);

	/*----> UInt8 ~ length_a <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_octet_string->length_a < 0 || p_octet_string->length_a > MAX_OCTET_STRING_LEN) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_octet_string->length_a should be in range [ 0 - MAX_OCTET_STRING_LEN]"
		            "Incorrect value: %d", p_octet_string->length_a);
		        return GNB_FAILURE;

	    }

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_octet_string->length_a);

	/*----> UInt16 ~ data_a <----*/ 

	    /* Get length of OCTET_STRING VARIABLE of basic type elements */
	    length += (p_octet_string->length_a * sizeof(p_octet_string->data_a[0]));

	    return length;
}

/* compose */
static
gnb_return_et
gnb_il_compose_octet_string
(
    UInt8 **pp_buffer,
    octet_string_t * p_octet_string
){
	    GNB_ASSERT(pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(p_octet_string != GNB_P_NULL);

	    /* This function composes octet_string */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing octet_string");

	/*----> UInt8 ~ length_a <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_octet_string->length_a < 0 || p_octet_string->length_a > MAX_OCTET_STRING_LEN) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_octet_string->length_a should be in range [ 0 - MAX_OCTET_STRING_LEN]"
		            "Incorrect value: %d", p_octet_string->length_a);
		        return GNB_FAILURE;

	    }

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt8(*pp_buffer, &p_octet_string->length_a, "length_a");
	    *pp_buffer += sizeof(p_octet_string->length_a);

	/*----> UInt16 ~ data_a <----*/ 

	    /* Compose OCTET_STRING VARIABLE of basic type elements */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < p_octet_string->length_a; loop++)
		        {
			            gnb_cp_pack_UInt16(*pp_buffer, &p_octet_string->data_a[loop], "data_a[]");
			            *pp_buffer += sizeof(UInt16);
		        }
	    }

	    return GNB_SUCCESS;
}

/* get length */
static
gnb_length_t
gnb_il_get_dunglieu_len 
(
    dunglieu_t * p_dunglieu
){
	    gnb_length_t length = 0;
	    GNB_ASSERT(p_dunglieu != GNB_P_NULL);

	/*----> UInt8 ~ haha <----*/ 

	    /* Get length of OCTET_STRING FIXED of basic type elements */
	    length += sizeof(p_dunglieu->haha);

	/*----> UInt16 ~ hihi <----*/ 

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_dunglieu->hihi);

	    return length;
}

/* compose */
static
gnb_return_et
gnb_il_compose_dunglieu
(
    UInt8 **pp_buffer,
    dunglieu_t * p_dunglieu
){
	    GNB_ASSERT(pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(p_dunglieu != GNB_P_NULL);

	    /* This function composes dunglieu */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing dunglieu");

	/*----> UInt8 ~ haha <----*/ 

	    /* Compose of OCTET_STRING FIXED of basic type elements */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < ARRSIZE(p_dunglieu->haha); loop++)
		        {
			            gnb_cp_pack_UInt8(*pp_buffer, &p_dunglieu->haha[loop], "haha[]");
			            *pp_buffer += sizeof(UInt8);
		        }
	    }

	/*----> UInt16 ~ hihi <----*/ 

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt16(*pp_buffer, &p_dunglieu->hihi, "hihi");
	    *pp_buffer += sizeof(p_dunglieu->hihi);

	    return GNB_SUCCESS;
}

/* get length */
static
gnb_length_t
gnb_il_get_manhdung_len 
(
    manhdung_t * p_manhdung
){
	    gnb_length_t length = 0;
	    GNB_ASSERT(p_manhdung != GNB_P_NULL);

	/*----> UInt16 ~ numbits <----*/ 

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_manhdung->numbits);

	/*----> UInt8 ~ data <----*/ 

	    /* Get length of OCTET_STRING VARIABLE of basic type elements */
	    length += (p_manhdung->numbits * sizeof(p_manhdung->data[0]));

	    return length;
}

/* compose */
static
gnb_return_et
gnb_il_compose_manhdung
(
    UInt8 **pp_buffer,
    manhdung_t * p_manhdung
){
	    GNB_ASSERT(pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(p_manhdung != GNB_P_NULL);

	    /* This function composes manhdung */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing manhdung");

	/*----> UInt16 ~ numbits <----*/ 

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt16(*pp_buffer, &p_manhdung->numbits, "numbits");
	    *pp_buffer += sizeof(p_manhdung->numbits);

	/*----> UInt8 ~ data <----*/ 

	    /* Compose OCTET_STRING VARIABLE of basic type elements */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < p_manhdung->numbits; loop++)
		        {
			            gnb_cp_pack_UInt8(*pp_buffer, &p_manhdung->data[loop], "data[]");
			            *pp_buffer += sizeof(UInt8);
		        }
	    }

	    return GNB_SUCCESS;
}

/* get length */
static
gnb_length_t
gnb_il_get_band_parameters_len 
(
    band_parameters_t * p_band_parameters
){
	    gnb_length_t length = 0;
	    GNB_ASSERT(p_band_parameters != GNB_P_NULL);

	/*----> rrc_bitmask_t ~ present_bitmask <----*/ 

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_band_parameters->present_bitmask);

	/*----> UInt8 ~ band_id <----*/ 

	    /* Check for correct range [H - higher boundary] */
	    if(p_band_parameters->band_id > 3)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->band_id should be less than or equal to 3"
		            "Incorrect value: %d", p_band_parameters->band_id);
		        return GNB_FAILURE;

	    }

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_band_parameters->band_id);

	/*----> UInt16 ~ frequency <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_band_parameters->frequency < 0 || p_band_parameters->frequency > 6000) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->frequency should be in range [ 0 - 6000]"
		            "Incorrect value: %d", p_band_parameters->frequency);
		        return GNB_FAILURE;

	    }

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_band_parameters->frequency);

	/*----> UInt8 ~ optional_param_id <----*/ 

	    /* Optional element */
	    if(p_band_parameters->present_bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT)
	    {

		    /* Check for correct range [H - higher boundary] */
		    if(p_band_parameters->optional_param_id > 10)
		    {
			        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->optional_param_id should be less than or equal to 10"
			            "Incorrect value: %d", p_band_parameters->optional_param_id);
			        return GNB_FAILURE;

		    }

		    /* Get length of parameter of basic type */
		    length += (gnb_length_t)sizeof(p_band_parameters->optional_param_id);

	    }

	/*----> UInt8 ~ optional_param_data <----*/ 

	    /* Optional element */
	    if(p_band_parameters->present_bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT)
	    {

		    /* Check for correct range [B - both higher and lower boundary] */
		    if(p_band_parameters->optional_param_data < 0 || p_band_parameters->optional_param_data > 255) 
		    {
			        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->optional_param_data should be in range [ 0 - 255]"
			            "Incorrect value: %d", p_band_parameters->optional_param_data);
			        return GNB_FAILURE;

		    }

		    /* Get length of parameter of basic type */
		    length += (gnb_length_t)sizeof(p_band_parameters->optional_param_data);

	    }

	/*----> dunglieu_t ~ NHL <----*/ 

	    /* Get length of OCTET_STRING FIXED of IEs */
	        //:))))
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < ARRSIZE(p_band_parameters->NHL); loop++)
		        {
			            length += gnb_il_get_dunglieu_len(&p_band_parameters->NHL[loop]);
		        }
	    }

	/*----> manhdung_t ~ MD <----*/ 

	    /* Get length of IE */
	    length += gnb_il_get_manhdung_len(&p_band_parameters->MD);

	    return length;
}

/* compose */
static
gnb_return_et
gnb_il_compose_band_parameters
(
    UInt8 **pp_buffer,
    band_parameters_t * p_band_parameters
){
	    GNB_ASSERT(pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(p_band_parameters != GNB_P_NULL);

	    /* This function composes band_parameters */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing band_parameters");

	/*----> rrc_bitmask_t ~ present_bitmask <----*/ 

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt16(*pp_buffer, &p_band_parameters->present_bitmask, "present_bitmask");
	    *pp_buffer += sizeof(p_band_parameters->present_bitmask);

	/*----> UInt8 ~ band_id <----*/ 

	    /* Check for correct range [H - higher boundary] */
	    if(p_band_parameters->band_id > 3)
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->band_id should be less than or equal to 3"
		            "Incorrect value: %d", p_band_parameters->band_id);
		        return GNB_FAILURE;

	    }

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt8(*pp_buffer, &p_band_parameters->band_id, "band_id");
	    *pp_buffer += sizeof(p_band_parameters->band_id);

	/*----> UInt16 ~ frequency <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_band_parameters->frequency < 0 || p_band_parameters->frequency > 6000) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->frequency should be in range [ 0 - 6000]"
		            "Incorrect value: %d", p_band_parameters->frequency);
		        return GNB_FAILURE;

	    }

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt16(*pp_buffer, &p_band_parameters->frequency, "frequency");
	    *pp_buffer += sizeof(p_band_parameters->frequency);

	/*----> UInt8 ~ optional_param_id <----*/ 

	    /* Optional element */
	    if(p_band_parameters->present_bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT)
	    {

		    /* Check for correct range [H - higher boundary] */
		    if(p_band_parameters->optional_param_id > 10)
		    {
			        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->optional_param_id should be less than or equal to 10"
			            "Incorrect value: %d", p_band_parameters->optional_param_id);
			        return GNB_FAILURE;

		    }

		    /* Compose parameter of basic type */
		    gnb_cp_pack_UInt8(*pp_buffer, &p_band_parameters->optional_param_id, "optional_param_id");
		    *pp_buffer += sizeof(p_band_parameters->optional_param_id);

	    }

	/*----> UInt8 ~ optional_param_data <----*/ 

	    /* Optional element */
	    if(p_band_parameters->present_bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT)
	    {

		    /* Check for correct range [B - both higher and lower boundary] */
		    if(p_band_parameters->optional_param_data < 0 || p_band_parameters->optional_param_data > 255) 
		    {
			        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_band_parameters->optional_param_data should be in range [ 0 - 255]"
			            "Incorrect value: %d", p_band_parameters->optional_param_data);
			        return GNB_FAILURE;

		    }

		    /* Compose parameter of basic type */
		    gnb_cp_pack_UInt8(*pp_buffer, &p_band_parameters->optional_param_data, "optional_param_data");
		    *pp_buffer += sizeof(p_band_parameters->optional_param_data);

	    }

	/*----> dunglieu_t ~ NHL <----*/ 

	    /* Compose of OCTET_STRING FIXED of basic type elements */
	    {
		        :))))
		        gnb_counter_t loop;
		        for(loop = 0; loop < ARRSIZE(p_band_parameters->NHL); loop++)
		        {
			            if(GNB_FAILURE == gnb_il_compose_dunglieu(pp_buffer, &p_band_parameters->NHL[loop]))
			            {
				                return GNB_FAILURE;
			            }
		        }

	    }

	/*----> manhdung_t ~ MD <----*/ 

	    /* Compose IE */
	    if(GNB_FAILURE == gnb_il_compose_manhdung(pp_buffer, &p_band_parameters->MD))
	    {
		        return GNB_FAILURE;
	    }

	    return GNB_SUCCESS;
}

/* get length */
static
gnb_length_t
gnb_il_get_rf_parameters_len 
(
    rf_parameters_t * p_rf_parameters
){
	    gnb_length_t length = 0;
	    GNB_ASSERT(p_rf_parameters != GNB_P_NULL);

	/*----> rrc_bitmask_t ~ bitmask <----*/ 

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_rf_parameters->bitmask);

	/*----> UInt16 ~ id <----*/ 

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_rf_parameters->id);

	/*----> UInt8 ~ nmd <----*/ 

	    /* Get length of OCTET_STRING FIXED of basic type elements */
	    length += sizeof(p_rf_parameters->nmd);

	/*----> UInt8 ~ num_bands <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_rf_parameters->num_bands < 0 || p_rf_parameters->num_bands > MAX_BANDS) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_rf_parameters->num_bands should be in range [ 0 - MAX_BANDS]"
		            "Incorrect value: %d", p_rf_parameters->num_bands);
		        return GNB_FAILURE;

	    }

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_rf_parameters->num_bands);

	/*----> band_parameters_t ~ bands <----*/ 

	    /* Get length of OCTET_STRING VARIABLE of IE */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < p_rf_parameters->num_bands; loop++)
		        {
			            length += gnb_il_get_band_parameters_len(&p_rf_parameters->bands[loop]);
		        }
	    }

	/*----> octet_string_t ~ config_blob <----*/ 

	    /* Optional element */
	    if(p_rf_parameters->bitmask & RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT)
	    {

		    /* Get length of OCTET_STRING FIXED of IEs */
		        //:))))
		    {
			        gnb_counter_t loop;
			        for(loop = 0; loop < ARRSIZE(p_rf_parameters->config_blob); loop++)
			        {
				            length += gnb_il_get_octet_string_len(&p_rf_parameters->config_blob[loop]);
			        }
		    }

	    }

	    return length;
}

/* compose */
static
gnb_return_et
gnb_il_compose_rf_parameters
(
    UInt8 **pp_buffer,
    rf_parameters_t * p_rf_parameters
){
	    GNB_ASSERT(pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(p_rf_parameters != GNB_P_NULL);

	    /* This function composes rf_parameters */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing rf_parameters");

	/*----> rrc_bitmask_t ~ bitmask <----*/ 

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt16(*pp_buffer, &p_rf_parameters->bitmask, "bitmask");
	    *pp_buffer += sizeof(p_rf_parameters->bitmask);

	/*----> UInt16 ~ id <----*/ 

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt16(*pp_buffer, &p_rf_parameters->id, "id");
	    *pp_buffer += sizeof(p_rf_parameters->id);

	/*----> UInt8 ~ nmd <----*/ 

	    /* Compose of OCTET_STRING FIXED of basic type elements */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < ARRSIZE(p_rf_parameters->nmd); loop++)
		        {
			            gnb_cp_pack_UInt8(*pp_buffer, &p_rf_parameters->nmd[loop], "nmd[]");
			            *pp_buffer += sizeof(UInt8);
		        }
	    }

	/*----> UInt8 ~ num_bands <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_rf_parameters->num_bands < 0 || p_rf_parameters->num_bands > MAX_BANDS) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_rf_parameters->num_bands should be in range [ 0 - MAX_BANDS]"
		            "Incorrect value: %d", p_rf_parameters->num_bands);
		        return GNB_FAILURE;

	    }

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt8(*pp_buffer, &p_rf_parameters->num_bands, "num_bands");
	    *pp_buffer += sizeof(p_rf_parameters->num_bands);

	/*----> band_parameters_t ~ bands <----*/ 

	    /* Compose OCTET_STRING VARIABLE of IE */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < p_rf_parameters->num_bands; loop++)
		        {
			            if(GNB_FAILURE == gnb_il_compose_band_parameters(pp_buffer, &p_rf_parameters->bands[loop]))
			            {
				                return GNB_FAILURE;
			            }
		        }
	    }

	/*----> octet_string_t ~ config_blob <----*/ 

	    /* Optional element */
	    if(p_rf_parameters->bitmask & RF_PARAM_BITMASK_CONFIG_BLOB_PRESENT)
	    {

		    /* Compose of OCTET_STRING FIXED of basic type elements */
		    {
			        :))))
			        gnb_counter_t loop;
			        for(loop = 0; loop < ARRSIZE(p_rf_parameters->config_blob); loop++)
			        {
				            if(GNB_FAILURE == gnb_il_compose_octet_string(pp_buffer, &p_rf_parameters->config_blob[loop]))
				            {
					                return GNB_FAILURE;
				            }
			        }

		    }

	    }

	    return GNB_SUCCESS;
}

/* get length */
static
gnb_length_t
gnb_il_get_plmn_id_len 
(
    plmn_id_t * p_plmn_id
){
	    gnb_length_t length = 0;
	    GNB_ASSERT(p_plmn_id != GNB_P_NULL);

	/*----> UInt8 ~ plmn_count <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_plmn_id->plmn_count < 0 || p_plmn_id->plmn_count > MAX_OCTET_STRING_LEN) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_plmn_id->plmn_count should be in range [ 0 - MAX_OCTET_STRING_LEN]"
		            "Incorrect value: %d", p_plmn_id->plmn_count);
		        return GNB_FAILURE;

	    }

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_plmn_id->plmn_count);

	/*----> UInt8 ~ data <----*/ 

	    /* Get length of OCTET_STRING VARIABLE of basic type elements */
	    length += (p_plmn_id->plmn_count * sizeof(p_plmn_id->data[0]));

	    return length;
}

/* compose */
static
gnb_return_et
gnb_il_compose_plmn_id
(
    UInt8 **pp_buffer,
    plmn_id_t * p_plmn_id
){
	    GNB_ASSERT(pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(p_plmn_id != GNB_P_NULL);

	    /* This function composes plmn_id */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing plmn_id");

	/*----> UInt8 ~ plmn_count <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_plmn_id->plmn_count < 0 || p_plmn_id->plmn_count > MAX_OCTET_STRING_LEN) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_plmn_id->plmn_count should be in range [ 0 - MAX_OCTET_STRING_LEN]"
		            "Incorrect value: %d", p_plmn_id->plmn_count);
		        return GNB_FAILURE;

	    }

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt8(*pp_buffer, &p_plmn_id->plmn_count, "plmn_count");
	    *pp_buffer += sizeof(p_plmn_id->plmn_count);

	/*----> UInt8 ~ data <----*/ 

	    /* Compose OCTET_STRING VARIABLE of basic type elements */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < p_plmn_id->plmn_count; loop++)
		        {
			            gnb_cp_pack_UInt8(*pp_buffer, &p_plmn_id->data[loop], "data[]");
			            *pp_buffer += sizeof(UInt8);
		        }
	    }

	    return GNB_SUCCESS;
}

/* get length */
static
gnb_length_t
gnb_il_get_device_config_len 
(
    device_config_t * p_device_config
){
	    gnb_length_t length = 0;
	    GNB_ASSERT(p_device_config != GNB_P_NULL);

	/*----> UInt16 ~ bitmask <----*/ 

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_device_config->bitmask);

	/*----> UInt8 ~ version <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_device_config->version < 0 || p_device_config->version > 255) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_device_config->version should be in range [ 0 - 255]"
		            "Incorrect value: %d", p_device_config->version);
		        return GNB_FAILURE;

	    }

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_device_config->version);

	/*----> rf_parameters_t ~ rf_params <----*/ 

	    /* Get length of IE */
	    length += gnb_il_get_rf_parameters_len(&p_device_config->rf_params);

	/*----> UInt8 ~ extra_data_config <----*/ 

	    /* Optional element */
	    if(p_device_config->bitmask & CONFIG_PRESENT)
	    {

		    /* Get length of parameter of basic type */
		    length += (gnb_length_t)sizeof(p_device_config->extra_data_config);

	    }

	/*----> octet_string_t ~ extra_data <----*/ 

	    /* Optional element */
	    if(p_device_config->bitmask & DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT)
	    {

		    /* Get length of OCTET_STRING FIXED of IEs */
		        //:))))
		    {
			        gnb_counter_t loop;
			        for(loop = 0; loop < ARRSIZE(p_device_config->extra_data); loop++)
			        {
				            length += gnb_il_get_octet_string_len(&p_device_config->extra_data[loop]);
			        }
		    }

	    }

	/*----> UInt16 ~ band_count <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_device_config->band_count < 0 || p_device_config->band_count > MAX_COUNT) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_device_config->band_count should be in range [ 0 - MAX_COUNT]"
		            "Incorrect value: %d", p_device_config->band_count);
		        return GNB_FAILURE;

	    }

	    /* Get length of parameter of basic type */
	    length += (gnb_length_t)sizeof(p_device_config->band_count);

	/*----> band_parameters_t ~ band_data <----*/ 

	    /* Get length of OCTET_STRING VARIABLE of IE */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < p_device_config->band_count; loop++)
		        {
			            length += gnb_il_get_band_parameters_len(&p_device_config->band_data[loop]);
		        }
	    }

	/*----> UInt8 ~ list_id <----*/ 

	    /* Get length of OCTET_STRING FIXED of basic type elements */
	    length += sizeof(p_device_config->list_id);

	/*----> plmn_id_t ~ plmn <----*/ 

	    /* Get length of IE */
	    length += gnb_il_get_plmn_id_len(&p_device_config->plmn);

	/*----> TEST_PRINT ~ test_print <----*/ 

	    /* Get length of IE */
	    length += gnb_il_get_TEST_PRINT_len(&p_device_config->test_print);

	    return length;
}

/* compose */
static
gnb_return_et
gnb_il_compose_device_config
(
    UInt8 **pp_buffer,
    device_config_t * p_device_config
){
	    GNB_ASSERT(pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(*pp_buffer != GNB_P_NULL);
	    GNB_ASSERT(p_device_config != GNB_P_NULL);

	    /* This function composes device_config */
	    GNB_CP_TRACE(GNB_DETAILEDALL, "dungnm26 - Composing device_config");

	/*----> UInt16 ~ bitmask <----*/ 

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt16(*pp_buffer, &p_device_config->bitmask, "bitmask");
	    *pp_buffer += sizeof(p_device_config->bitmask);

	/*----> UInt8 ~ version <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_device_config->version < 0 || p_device_config->version > 255) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_device_config->version should be in range [ 0 - 255]"
		            "Incorrect value: %d", p_device_config->version);
		        return GNB_FAILURE;

	    }

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt8(*pp_buffer, &p_device_config->version, "version");
	    *pp_buffer += sizeof(p_device_config->version);

	/*----> rf_parameters_t ~ rf_params <----*/ 

	    /* Compose IE */
	    if(GNB_FAILURE == gnb_il_compose_rf_parameters(pp_buffer, &p_device_config->rf_params))
	    {
		        return GNB_FAILURE;
	    }

	/*----> UInt8 ~ extra_data_config <----*/ 

	    /* Optional element */
	    if(p_device_config->bitmask & CONFIG_PRESENT)
	    {

		    /* Compose parameter of basic type */
		    gnb_cp_pack_UInt8(*pp_buffer, &p_device_config->extra_data_config, "extra_data_config");
		    *pp_buffer += sizeof(p_device_config->extra_data_config);

	    }

	/*----> octet_string_t ~ extra_data <----*/ 

	    /* Optional element */
	    if(p_device_config->bitmask & DEVICE_CONFIG_BITMASK_EXTRA_DATA_PRESENT)
	    {

		    /* Compose of OCTET_STRING FIXED of basic type elements */
		    {
			        :))))
			        gnb_counter_t loop;
			        for(loop = 0; loop < ARRSIZE(p_device_config->extra_data); loop++)
			        {
				            if(GNB_FAILURE == gnb_il_compose_octet_string(pp_buffer, &p_device_config->extra_data[loop]))
				            {
					                return GNB_FAILURE;
				            }
			        }

		    }

	    }

	/*----> UInt16 ~ band_count <----*/ 

	    /* Check for correct range [B - both higher and lower boundary] */
	    if(p_device_config->band_count < 0 || p_device_config->band_count > MAX_COUNT) 
	    {
		        GNB_CP_TRACE(GNB_WARNING, "dungnm26 - Parameter p_device_config->band_count should be in range [ 0 - MAX_COUNT]"
		            "Incorrect value: %d", p_device_config->band_count);
		        return GNB_FAILURE;

	    }

	    /* Compose parameter of basic type */
	    gnb_cp_pack_UInt16(*pp_buffer, &p_device_config->band_count, "band_count");
	    *pp_buffer += sizeof(p_device_config->band_count);

	/*----> band_parameters_t ~ band_data <----*/ 

	    /* Compose OCTET_STRING VARIABLE of IE */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < p_device_config->band_count; loop++)
		        {
			            if(GNB_FAILURE == gnb_il_compose_band_parameters(pp_buffer, &p_device_config->band_data[loop]))
			            {
				                return GNB_FAILURE;
			            }
		        }
	    }

	/*----> UInt8 ~ list_id <----*/ 

	    /* Compose of OCTET_STRING FIXED of basic type elements */
	    {
		        gnb_counter_t loop;
		        for(loop = 0; loop < ARRSIZE(p_device_config->list_id); loop++)
		        {
			            gnb_cp_pack_UInt8(*pp_buffer, &p_device_config->list_id[loop], "list_id[]");
			            *pp_buffer += sizeof(UInt8);
		        }
	    }

	/*----> plmn_id_t ~ plmn <----*/ 

	    /* Compose IE */
	    if(GNB_FAILURE == gnb_il_compose_plmn_id(pp_buffer, &p_device_config->plmn))
	    {
		        return GNB_FAILURE;
	    }

	/*----> TEST_PRINT ~ test_print <----*/ 

	    /* Compose IE */
	    if(GNB_FAILURE == gnb_il_compose_TEST_PRINT(pp_buffer, &p_device_config->test_print))
	    {
		        return GNB_FAILURE;
	    }

	    return GNB_SUCCESS;
}

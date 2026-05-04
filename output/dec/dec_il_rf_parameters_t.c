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




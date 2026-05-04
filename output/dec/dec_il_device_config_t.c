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




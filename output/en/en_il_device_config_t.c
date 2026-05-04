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
        //:))))
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


        
        
    
        
        
        



    return GNG_SUCCESS;
}




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




/* get length */
static
gnb_length_t
gnb_il_get_band_parameters_len 
(
    band_parameters_t * p_band_parameters
){
    gnb_length_t length = 0;
    GNB_ASSERT(p_band_parameters != GNB_P_NULL);

/*----> rrc_bitmask_t ~ bitmask <----*/ 





    /* Get length of parameter of basic type */
    length += (gnb_length_t)sizeof(p_band_parameters->bitmask);



        
        
    
        
                
        


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
    if(p_band_parameters->bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT)
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
    if(p_band_parameters->bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT)
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

/*----> rrc_bitmask_t ~ bitmask <----*/ 





    /* Compose parameter of basic type */
    gnb_cp_pack_UInt16(*pp_buffer, &p_band_parameters->bitmask, "bitmask");
    *pp_buffer += sizeof(p_band_parameters->bitmask);



        
        
    
        
        
        


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
    if(p_band_parameters->bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_ID_PRESENT)
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
    if(p_band_parameters->bitmask & BAND_PARAM_BITMASK_OPTIONAL_PARAM_DATA_PRESENT)
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


    return GNG_SUCCESS;
}




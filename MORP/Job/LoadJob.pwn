CB:LoadJob()
{
    new rows;
    cache_get_row_count(rows);
    if(rows){
        for(new i = 0; i < rows; i++){
            cache_get_value_int(i, "JobID", gJobData[i][jID]);
            cache_get_value_name(i, "JobName", gJobData[i][jName]);
            cache_get_value_int(i, "JobType", gJobData[i][jType]);
            cache_get_value_int(i, "JobSkin", gJobData[i][jSkin]);
            cache_get_value_int(i, "JobSalary", gJobData[i][jSalary]);
            cache_get_value_int(i, "JobOwnerID", gJobData[i][jOwnerID]);
            cache_get_value_float(i, "JobPosX", gJobData[i][jPos][0]);
            cache_get_value_float(i, "JobPosY", gJobData[i][jPos][1]);
            cache_get_value_float(i, "JobPosZ", gJobData[i][jPos][2]);
            cache_get_value_name(i, "JobOwner", gJobData[i][jOwner]);
            gJobData[i][jExists] = true;
            ReloadJob(i);
        }
    }
}

stock ReloadJob(jobid){
    new string[128];
    if(gJobData[jobid][jExists]){
        format(string, sizeof(string), ""COLOR_YELLOW"%s(%d)\n"COLOR_WHITE"Salary: "COLOR_YELLOW"$%d\n"COLOR_WHITE"Owner: "COLOR_YELLOW"%s\n",
            gJobData[jobid][jName],
            jobid,
            gJobData[jobid][jSalary],
            gJobData[jobid][jOwner]);
        if(IsValidDynamicPickup(gJobData[jobid][jPickup])){
            DestroyDynamicPickup(gJobData[jobid][jPickup]);
        }
        if(IsValidDynamic3DTextLabel(gJobData[jobid][jLabel])){
            DestroyDynamic3DTextLabel(gJobData[jobid][jLabel]);
        }
        gJobData[jobid][jLabel] = CreateDynamic3DTextLabel(string, SERVER_COLOR, gJobData[jobid][jPos][0], gJobData[jobid][jPos][1], gJobData[jobid][jPos][2], 20.0, .worldid = -1, .interiorid = -1);
        gJobData[jobid][jPickup] = CreateDynamicPickup(1239, 23, gJobData[jobid][jPos][0], gJobData[jobid][jPos][1], gJobData[jobid][jPos][2], -1, -1, -1, 20.0);
    }
}
hook OnGameModeInit()
{
    mysql_tquery(db, "SELECT * FROM `Jobs`", "LoadJob");
    return 1;
}
/* Create Job */

new TempJobName[64];

stock bool:DoesJobExistByID(jobid)
{
    if(jobid < 0 || jobid >= MAX_JOBS) return false;
    return gJobData[jobid][jExists];
}
stock bool:DoesJobExist(const Name[])
{
    mysql_format(db, DB_query, sizeof(DB_query), "SELECT * FROM Jobs WHERE JobName = '%e'", Name);
    new Cache:result = mysql_query(db, DB_query), rows;
    cache_get_row_count(rows);
    if(rows)
    {
        cache_delete(result);
        return true;
    }
    cache_delete(result);
    return false;
}

stock bool:CreateJob(playerid, const Name[] = "NULL", Type, skin, Salary, PlayerID = -1, Float:PosX = 0.0, Float:PosY = 0.0, Float:PosZ = 0.0)
{
    new OwnerID, Owner[MAX_PLAYER_NAME + 1], jobid;
    if(IsPlayerConnected(PlayerID))
    {
        OwnerID = gPlayerData[PlayerID][pID];
        strcpy(Owner, gPlayerData[PlayerID][pName]);
    }
    else
    {
        OwnerID = 0;
        strcpy(Owner, "Govt.");
    }
    if(strcmp(Name, "NULL", true) == 0) return SEM(playerid, "Oops! You forgot to enter a job name.");
    if(DoesJobExist(Name)) return SEM(playerid, "Oops! This job already exists.");
    if(Type < 1 || Type > 2) return SEM(playerid, "Oops! Invalid job type.");
    if(skin < 0 || skin > 312) return SEM(playerid, "Oops! Invalid skin ID.");
    if(Salary < 100) return SEM(playerid, "Oops! Invalid salary.");

    GetPlayerPos(playerid, PosX, PosY, PosZ);
    for(new i = 0; i != MAX_JOBS; i++)
    {
        if(!gJobData[i][jExists])
        {
            gJobData[i][jExists] = true;
            strcpy(gJobData[i][jName], Name);
            gJobData[i][jType] = Type;
            gJobData[i][jSkin] = skin;
            gJobData[i][jSalary] = Salary;
            gJobData[i][jOwnerID] = OwnerID;
            strcpy(gJobData[i][jOwner], Owner);
            gJobData[i][jPos][0] = PosX;
            gJobData[i][jPos][1] = PosY;
            gJobData[i][jPos][2] = PosZ;
            jobid = i;
            break;
        }
        else{
            if(i == MAX_JOBS - 1) return SEM(playerid, "Oops! Maximum job limit reached.");
        }
    }
    mysql_format(db, DB_query, sizeof(DB_query), "INSERT INTO Jobs (JobName, JobType, JobSkin, JobSalary, JobOwnerID, JobOwner, JobPosX, JobPosY, JobPosZ) VALUES ('%e', %d, %d, %d, %d, '%e', %f, %f, %f)", Name, Type, skin, Salary, OwnerID, Owner, PosX, PosY, PosZ);
    mysql_tquery(db, DB_query, "OnJobCreated", "ii", playerid, jobid);
    return true;
}

CB: OnJobCreated(playerid, jobid)
{
    gJobData[jobid][jID] = cache_insert_id();
    new string[128];
    format(string, sizeof(string), "Job created successfully. ID: %d", jobid);
    SSM(playerid, string);
    ReloadJob(jobid);
    return 1;
}

Dialog:ShowDialogCreateJob1(playerid, response, listitem, inputtext[])
{
    if(response)
    {
        if(!strlen(inputtext)){
            ShowDialog(playerid, DIALOG_CREATE_JOB1);
            SEM(playerid, "Oops! You forgot to enter a job name.");
            return 1;
        }
        strcpy(TempJobName, inputtext);
        ShowDialog(playerid, DIALOG_CREATE_JOB2);
        return 1;
    }
    return 1;
}

Dialog:ShowDialogCreateJob2(playerid, response, listitem, inputtext[])
{
    new Type, skin, Salary, PlayerID;
    if(response)
    {
        if(sscanf(inputtext, "p<,>iiii", Type, skin, Salary, PlayerID))
        {
            ShowDialog(playerid, DIALOG_CREATE_JOB2);
            SEM(playerid, "Usage: /createjob");
            return 1;
        }
        CreateJob(playerid, TempJobName, Type, skin, Salary, PlayerID);
        return 1;
    }
    return 1;
}

stock bool:EditJob(playerid, jobid, Type, skin, Salary)
{
    if(!DoesJobExistByID(jobid)) return SEM(playerid, "Oops! This job does not exist.");
    if(Type < 1 || Type > 2) return SEM(playerid, "Oops! Invalid job type.");
    if(skin < 0 || skin > 312) return SEM(playerid, "Oops! Invalid skin ID.");
    if(Salary < 100) return SEM(playerid, "Oops! Invalid salary.");

    gJobData[jobid][jType] = Type;
    gJobData[jobid][jSkin] = skin;
    gJobData[jobid][jSalary] = Salary;
    mysql_format(db, DB_query, sizeof(DB_query), "UPDATE Jobs SET JobType = %d, JobSkin = %d, JobSalary = %d WHERE JobName = '%e'", Type, skin, Salary, gJobData[jobid][jName]);
    mysql_tquery(db, DB_query);
    SSM(playerid, "Job edited successfully.");
    return true;
}

stock bool:DeleteJob(playerid, jobid)
{
    if(!bool:DoesJobExistByID(jobid)) return SEM(playerid, "Oops! This job does not exist.");
    
    gJobData[jobid][jExists] = false;
    if(IsValidDynamicPickup(gJobData[jobid][jPickup])){
        DestroyDynamicPickup(gJobData[jobid][jPickup]);
    }
    if(IsValidDynamic3DTextLabel(gJobData[jobid][jLabel])){
        DestroyDynamic3DTextLabel(gJobData[jobid][jLabel]);
    }
    mysql_format(db, DB_query, sizeof(DB_query), "DELETE FROM Jobs WHERE JobName = '%e'", gJobData[jobid][jName]);
    mysql_tquery(db, DB_query);
    SSM(playerid, "Job deleted successfully.");
    ReloadJob(jobid);
    return true;
}

CMD:createjob(playerid, const params[])
{
    ShowDialog(playerid, DIALOG_CREATE_JOB1);
    return 1;
}

CMD:deletejob(playerid, const params[])
{
    new jobid;
    if(sscanf(params, "i", jobid))
    {
        return SEM(playerid, "Usage: /deletejob [JobID]");
    }
    DeleteJob(playerid, jobid);
    return 1;
}



CMD:editjob(playerid, const params[])
{
    new jobid, Type, skin, Salary;
    if(sscanf(params, "iiii", jobid, Type, skin, Salary))
    {
        return SEM(playerid, "Usage: /editjob [jobid] [Type] [Skin] [Salary]");
    }
    EditJob(playerid, jobid, Type, skin, Salary);
    return 1;
}


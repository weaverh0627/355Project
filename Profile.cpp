/* Ayanaaaaaaaaaaa*/

//For the movie table
#include <iostream>
#include <string>
#include <stdlib.h>

/*Drivers for SQL*/
#include "mysql_connection.h"

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

using namespace std;

int main()
{
    cout << endl;

    try {

    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
    sql::ResultSet *res;
    sql::PreparedStatement *prep_stmt;

    /* Create a connection */
    driver = get_driver_instance();
    con = driver->connect("tcp://deltona.birdnest.org:3306", "my.weaverh3", "r780t0b1");
    /* Connect to the MySQL test database */
    con->setSchema("my_weaverh3_groupProgrammingProject");

    stmt = con->createStatement();
    res = stmt->executeQuery("SELECT Name AS _column FROM Profile");
    while (res->next()) {
        cout << "\t... MySQL replies: ";
        /* Access column data by alias or column name */
        cout << res->getString("_column") << endl;
        cout << "\t... MySQL says it again: ";
        /* Access column data by numeric offset, 1 is the first column */
        cout << res->getString(1) << endl;
    }

    string actionType;
    cout << "input what action to perform: (C for Create, R for Read, U for Update, or D for delete) " << endl;
    cin >> actionType;

    if (actionType == "C" || actionType == "c" ) {

        string profileName;
        int acctID, profileID;
        cout << "Enter The Profile Name" << endl;
        cin.ignore();
        getline(cin, profileName);
        cout << "You inputed " + profileName << endl;
        cout << "Enter the Account ID";
        cin >> acctID;       
        
        prep_stmt = con->prepareStatement("INSERT INTO Profile (ProfileName,AcctID) VALUES ('?',?)");
        prep_stmt->setString(1,profileName);
        prep_stmt->setInt(2,acctID);
        prep_stmt->execute();

        delete prep_stmt;
        //res = stmt->executeQuery("SELECT Name AS _column FROM Profile"); 
    }

    else if (actionType == "R" || actionType == "r") {
        string columnName;
        cout << "Enter column name ";
        cin >> columnName;

        res = stmt->executeQuery("SELECT " + columnName + " AS _column FROM Profile"); 
    }

    else if (actionType == "U" || actionType == "u") {


        //string columnName, updatedVal; 
        //int userColumnChoice, mid;
        //cout << "Enter the movie id to update ";
        //cin >> mid; 
        //cout << "Enter a column to update ";
        //cin >> userColumnChoice;
        //cout << "Enter what to set the value to for the column you entered ";
        //cin.ignore();
        //getline(cin, updatedVal);
        
        /*
        switch (userColumnChoice) {
            case 1:
                columnName = "Name";
                break;
            case 2:
                columnName = "YearReleased";
                break;
            case 3:
                columnName = "Runtime";
                break;
            case 4:
                columnName = "Description";
                break; 
            default: 
                cout << "You didn't chose a valid column" << endl;   
                break;        
        } */
        
        string columnName;
        columnName = "PercentComplete";
        cout << "Enter an integer that is the new value for PercentComplete ";
        int updatedVal;
        cin >> updatedVal;
        //cout << "Enter the id number of the Movie you would like to update ";
        //cin >> userMovieName;

        prep_stmt = con->prepareStatement("UPDATE Profile SET " + columnName + " = ? WHERE Acctid = 1");
        prep_stmt->setInt(1,updatedVal);
        //prep_stmt->setInt(2,userMovieName);
        prep_stmt->execute();

        delete prep_stmt; 

    }

    else if (actionType == "D" || actionType == "d") {
        //DELETE FROM table_name WHERE condition;
        int profileToDelete;
        cin >> profileToDelete;

        prep_stmt = con->prepareStatement("DELETE FROM Profile WHERE id=?");
        prep_stmt->setInt(1,profileToDelete);
        prep_stmt->execute();

        delete prep_stmt; 

    }

    else {
        cout << "Error: you did not enter what action you would like to perform";
    }
    
    while (res->next()) {
        cout << "\t... MySQL replies: ";
        /* Access column data by alias or column name */
        cout << res->getString("_column") << endl;
        cout << "\t... MySQL says it again: ";
        /* Access column data by numeric offset, 1 is the first column */
        cout << res->getString(1) << endl;
    }

    //DELETES FOR POINTERS DONT MESS W THIS!!!!!!!!!!!!:D
    delete res;
    delete stmt;
    delete con;

    } catch (sql::SQLException &e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    return EXIT_SUCCESS;

    return 0;
    
}
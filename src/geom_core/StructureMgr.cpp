//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//

// StructureMgr.cpp
//
// Justin Gravett
//////////////////////////////////////////////////////////////////////

#include "StructureMgr.h"
#include "VehicleMgr.h"
#include "Vehicle.h"


StructureMgrSingleton::StructureMgrSingleton()
{
    InitFeaMaterials();
    m_FeaPropertyCount = 0;
    m_FeaMatCount = 0;
}

StructureMgrSingleton::~StructureMgrSingleton()
{
    // Delete FeaProperties
    for ( int i = 0; i < (int)m_FeaPropertyVec.size(); i++ )
    {
        delete m_FeaPropertyVec[i];
    }
    m_FeaPropertyVec.clear();

    // Delete FeaMaterials
    for ( int i = 0; i < (int)m_FeaMaterialVec.size(); i++ )
    {
        delete m_FeaMaterialVec[i];
    }
    m_FeaMaterialVec.clear();
}

xmlNodePtr StructureMgrSingleton::EncodeXml( xmlNodePtr & node )
{
    xmlNodePtr structmgr_node = xmlNewChild( node, NULL, BAD_CAST"StructureMgr", NULL );

    for ( int i = 0; i < (int)m_FeaPropertyVec.size(); i++ )
    {
        m_FeaPropertyVec[i]->EncodeXml( structmgr_node );
    }

    for ( int i = 0; i < (int)m_FeaMaterialVec.size(); i++ )
    {
        if ( m_FeaMaterialVec[i]->m_UserFeaMaterial )
        {
            m_FeaMaterialVec[i]->EncodeXml( structmgr_node );
        }
    }

    return structmgr_node;
}

xmlNodePtr StructureMgrSingleton::DecodeXml( xmlNodePtr & node )
{
    xmlNodePtr structmgr_node = XmlUtil::GetNode( node, "StructureMgr", 0 );

    if ( structmgr_node )
    {
        int num_prop = XmlUtil::GetNumNames( structmgr_node, "FeaPropertyInfo" );

        for ( unsigned int i = 0; i < num_prop; i++ )
        {
            xmlNodePtr prop_info = XmlUtil::GetNode( structmgr_node, "FeaPropertyInfo", i );

            if ( prop_info )
            {
                FeaProperty* fea_prop = new FeaProperty();
                fea_prop->DecodeXml( prop_info );
                AddFeaProperty( fea_prop );
            }
        }

        int num_mat = XmlUtil::GetNumNames( structmgr_node, "FeaMaterialInfo" );

        for ( unsigned int i = 0; i < num_mat; i++ )
        {
            xmlNodePtr mat_info = XmlUtil::GetNode( structmgr_node, "FeaMaterialInfo", i );

            if ( mat_info )
            {
                FeaMaterial* fea_mat = new FeaMaterial();
                fea_mat->DecodeXml( mat_info );
                fea_mat->m_UserFeaMaterial = true;

                AddFeaMaterial( fea_mat );
            }
        }
    }

    return node;
}

//==== Get All FeaStructures ====//
vector < FeaStructure* > StructureMgrSingleton::GetAllFeaStructs()
{
    vector < FeaStructure* > feastructvec;

    Vehicle* veh = VehicleMgr.GetVehicle();

    if ( veh )
    {
        vector< Geom* > geom_vec = veh->FindGeomVec( veh->GetGeomVec( false ) );

        for ( unsigned int i = 0; i < geom_vec.size(); i++ )
        {
            vector < FeaStructure* > geomstructvec = geom_vec[i]->GetFeaStructVec();

            for ( unsigned int j = 0; j < geomstructvec.size(); j++ )
            {
                feastructvec.push_back( geomstructvec[j] );
            }
        }
    }

    return feastructvec;
}

//==== Validate FeaStructure Index ====//
bool StructureMgrSingleton::ValidTotalFeaStructInd( int index )
{
    vector < FeaStructure* > feastructvec = GetAllFeaStructs();

    if ( (int)feastructvec.size() > 0 && index >= 0 && index < (int)feastructvec.size() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

int StructureMgrSingleton::NumFeaStructures()
{
    vector < FeaStructure* > struct_vec = GetAllFeaStructs();
    return struct_vec.size();
}

//==== Get FeaProperty Index =====//
int StructureMgrSingleton::GetFeaPropertyIndex( string FeaPartID )
{
    vector < FeaStructure* > struct_vec = GetAllFeaStructs();

    for ( unsigned int i = 0; i < struct_vec.size(); i++ )
    {
        FeaPart* found_part = struct_vec[i]->GetFeaPart( FeaPartID );

        if ( found_part )
        {
            return found_part->GetFeaPropertyIndex();
        }
    }

    return -1;
}

//==== Get FeaMaterial Index =====//
int StructureMgrSingleton::GetFeaMaterialIndex( string FeaPartID )
{
    vector < FeaStructure* > struct_vec = GetAllFeaStructs();

    for ( unsigned int i = 0; i < struct_vec.size(); i++ )
    {
        FeaPart* found_part = struct_vec[i]->GetFeaPart( FeaPartID );

        if ( found_part )
        {
            return found_part->GetFeaMaterialIndex();
        }
    }

    return -1;
}

//==== Add FeaProperty =====//
FeaProperty* StructureMgrSingleton::AddFeaProperty( int property_type )
{
    FeaProperty* feaprop = new FeaProperty();

    if ( feaprop )
    {
        feaprop->SetName( string( "FEA_PROPERTY_" + std::to_string( m_FeaPropertyCount ) ) );
        feaprop->m_FeaPropertyType.Set( property_type );
        m_FeaPropertyVec.push_back( feaprop );
        m_FeaPropertyCount++;
    }

    return feaprop;
}

//==== Delete FeaProperty =====//
void StructureMgrSingleton::DeleteFeaProperty( int index )
{
    if ( !ValidFeaPropertyInd( index ) )
        return;

    delete m_FeaPropertyVec[index];
    m_FeaPropertyVec.erase( m_FeaPropertyVec.begin() + index );
}

//==== Validate FeaProperty Index ====//
bool StructureMgrSingleton::ValidFeaPropertyInd( int index )
{
    if ( (int)m_FeaPropertyVec.size() > 0 && index >= 0 && index < (int)m_FeaPropertyVec.size() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

FeaProperty* StructureMgrSingleton::GetFeaProperty( int index )
{
    if ( ValidFeaPropertyInd( index ) )
    {
        return m_FeaPropertyVec[index];
    }
    else
    {
        return NULL;
    }
}

//==== Add FeaMaterial =====//
FeaMaterial* StructureMgrSingleton::AddFeaMaterial()
{
    FeaMaterial* feamat = new FeaMaterial();

    if ( feamat )
    {
        feamat->SetName( string( "FEA_MATERIAL_" + std::to_string( m_FeaMatCount ) ) );
        feamat->m_UserFeaMaterial = true;
        m_FeaMaterialVec.push_back( feamat );
        m_FeaMatCount++;
    }

    return feamat;
}

//==== Delete FeaMaterial =====//
void StructureMgrSingleton::DeleteFeaMaterial( int index )
{
    if ( !ValidFeaMaterialInd( index ) || !m_FeaMaterialVec[index]->m_UserFeaMaterial ) 
        return;

    delete m_FeaMaterialVec[index];
    m_FeaMaterialVec.erase( m_FeaMaterialVec.begin() + index );
}

//==== Validate FeaMaterial Index ====//
bool StructureMgrSingleton::ValidFeaMaterialInd( int index )
{
    if ( (int)m_FeaMaterialVec.size() > 0 && index >= 0 && index < (int)m_FeaMaterialVec.size() )
    {
        return true;
    }
    else
    {
        return false;
    }
}

FeaMaterial* StructureMgrSingleton::GetFeaMaterial( int index )
{
    if ( ValidFeaMaterialInd( index ) )
    {
        return m_FeaMaterialVec[index];
    }
    else
    {
        return NULL;
    }
}

void StructureMgrSingleton::InitFeaMaterials()
{
    // Reference: http://www.matweb.com/search/datasheet.aspx?bassnum=MA0001

    FeaMaterial* aluminum = new FeaMaterial();

    aluminum->SetName( "Aluminum" );
    aluminum->m_MassDensity.Set( 0.0975 ); // lb/in^3
    aluminum->m_ElasticModulus.Set( 10.2e6 ); // psi
    aluminum->m_PoissonRatio.Set( 0.33 );
    aluminum->m_ThermalExpanCoeff.Set( 1.33e-5 ); // in/(in-�F)
    aluminum->m_UserFeaMaterial = false;
    AddFeaMaterial( aluminum );

    FeaMaterial* steel = new FeaMaterial();

    steel->SetName( "Steel" );
    steel->m_MassDensity.Set( 0.284 ); // lb/in^3
    steel->m_ElasticModulus.Set( 29.0e6 ); // psi
    steel->m_PoissonRatio.Set( 0.30 );
    steel->m_ThermalExpanCoeff.Set( 6.67e-6 ); // in/(in-�F)
    steel->m_UserFeaMaterial = false;
    AddFeaMaterial( steel );
}

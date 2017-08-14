//
// This file is released under the terms of the NASA Open Source Agreement (NOSA)
// version 1.3 as detailed in the LICENSE file which accompanies this software.
//
//
//////////////////////////////////////////////////////////////////////

#include "BORScreen.h"
#include "ScreenMgr.h"
#include "BORGeom.h"
#include "ParmMgr.h"


//==== Constructor ====//
BORScreen::BORScreen( ScreenMgr* mgr ) : GeomScreen( mgr, 300, 680, "BOR" )
{
    Fl_Group* design_tab = AddTab( "Design" );
    Fl_Group* design_group = AddSubGroup( design_tab, 5 );

    m_DesignLayout.SetGroupAndScreen( design_group, this );
    m_DesignLayout.AddDividerBox( "Design" );

    //==== Design ====//

    m_ModeChoice.AddItem( "Flowthrough" );
    m_ModeChoice.AddItem( "Upper" );
    m_ModeChoice.AddItem( "Lower" );
    m_DesignLayout.AddChoice( m_ModeChoice, "Mode" );

    m_DesignLayout.AddYGap();

    m_DesignLayout.AddDividerBox( "Flowthrough Control" );
    m_DesignLayout.AddSlider( m_BORDiameterSlider, "Diameter", 10, "%7.3f" );
    m_DesignLayout.AddSlider( m_AngleSlider, "Angle", 10, "%7.3f" );

    m_DesignLayout.AddYGap();

    m_DesignLayout.AddDividerBox( "Tessellation Control" );
    m_DesignLayout.AddSlider( m_LEClusterSlider, "LE Clustering", 1, "%6.5f" );
    m_DesignLayout.AddSlider( m_TEClusterSlider, "TE Clustering", 1, "%6.5f" );


    m_DesignLayout.AddSlider( m_CapTessSlider, "Cap Tess", 10, "%3.0f" );


    //==== XSec ====//
    Fl_Group* xsec_tab = AddTab( "XSec" );
    Fl_Group* xsec_group = AddSubGroup( xsec_tab, 5 );

    m_XSecLayout.SetGroupAndScreen( xsec_group, this );
    m_XSecLayout.AddDividerBox( "Cross Section" );

    m_XSecLayout.AddYGap();

    m_XSecLayout.AddDividerBox( "Type" );

    m_XSecTypeChoice.AddItem( "POINT" );
    m_XSecTypeChoice.AddItem( "CIRCLE" );
    m_XSecTypeChoice.AddItem( "ELLIPSE" );
    m_XSecTypeChoice.AddItem( "SUPER_ELLIPSE" );
    m_XSecTypeChoice.AddItem( "ROUNDED_RECTANGLE" );
    m_XSecTypeChoice.AddItem( "GENERAL_FUSE" );
    m_XSecTypeChoice.AddItem( "FUSE_FILE" );
    m_XSecTypeChoice.AddItem( "FOUR_SERIES" );
    m_XSecTypeChoice.AddItem( "SIX_SERIES" );
    m_XSecTypeChoice.AddItem( "BICONVEX" );
    m_XSecTypeChoice.AddItem( "WEDGE" );
    m_XSecTypeChoice.AddItem( "BEZIER" );
    m_XSecTypeChoice.AddItem( "AF_FILE" );
    m_XSecTypeChoice.AddItem( "CST_AIRFOIL" );
    m_XSecTypeChoice.AddItem( "KARMAN_TREFFTZ" );

    m_XSecLayout.SetSameLineFlag( true );
    m_XSecLayout.AddChoice( m_XSecTypeChoice, "Choose Type:", m_XSecLayout.GetButtonWidth() );
    m_XSecLayout.SetFitWidthFlag( false );
    m_XSecLayout.AddButton( m_ShowXSecButton, "Show" );
    m_XSecLayout.ForceNewLine();

    m_XSecLayout.SetFitWidthFlag( true );
    m_XSecLayout.SetSameLineFlag( false );

    //==== Location To Start XSec Layouts ====//
    int start_y = m_XSecLayout.GetY();


    //==== Circle XSec ====//
    m_CircleGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_CircleGroup.SetY( start_y );
    m_CircleGroup.AddYGap();
    m_CircleGroup.AddSlider(  m_DiameterSlider, "Diameter", 10, "%6.5f" );

    //==== Ellipse XSec ====//
    m_EllipseGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_EllipseGroup.SetY( start_y );
    m_EllipseGroup.AddYGap();
    m_EllipseGroup.AddSlider(  m_EllipseHeightSlider, "Height", 10, "%6.5f" );
    m_EllipseGroup.AddSlider(  m_EllipseWidthSlider, "Width", 10, "%6.5f" );

    //==== Super XSec ====//
    m_SuperGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_SuperGroup.SetY( start_y );
    m_SuperGroup.AddYGap();
    m_SuperGroup.AddSlider( m_SuperHeightSlider, "Height", 10, "%6.5f" );
    m_SuperGroup.AddSlider( m_SuperWidthSlider,  "Width", 10, "%6.5f" );
    m_SuperGroup.AddYGap();
    m_SuperGroup.AddSlider( m_SuperMaxWidthLocSlider, "MaxWLoc", 2, "%6.5f" );
    m_SuperGroup.AddYGap();
    m_SuperGroup.AddSlider( m_SuperMSlider, "M", 10, "%6.5f" );
    m_SuperGroup.AddSlider( m_SuperNSlider, "N", 10, "%6.5f" );
    m_SuperGroup.AddYGap();
    m_SuperGroup.AddButton( m_SuperToggleSym, "T/B Symmetric Exponents" );
    m_SuperGroup.AddSlider( m_SuperM_botSlider, "M Bottom", 10, "%6.5f" );
    m_SuperGroup.AddSlider( m_SuperN_botSlider, "N Bottom", 10, "%6.5f" );

    //==== Rounded Rect ====//
    m_RoundedRectGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_RoundedRectGroup.SetY( start_y );
    m_RoundedRectGroup.AddYGap();
    m_RoundedRectGroup.AddSlider( m_RRHeightSlider, "Height", 10, "%6.5f" );
    m_RoundedRectGroup.AddSlider( m_RRWidthSlider,  "Width", 10, "%6.5f" );
    m_RoundedRectGroup.AddYGap();
    m_RoundedRectGroup.AddSlider( m_RRSkewSlider, "Skew", 2, "%6.5f");
    m_RoundedRectGroup.AddSlider( m_RRKeystoneSlider, "Keystone", 1, "%6.5f");
    m_RoundedRectGroup.AddYGap();
    m_RoundedRectGroup.AddSlider( m_RRRadiusSlider, "Radius", 10, "%6.5f" );
    m_RoundedRectGroup.AddYGap();
    m_RoundedRectGroup.AddButton( m_RRKeyCornerButton, "Key Corner" );

    //==== General Fuse XSec ====//
    m_GenGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_GenGroup.SetY( start_y );
    m_GenGroup.AddSlider( m_GenHeightSlider, "Height", 10, "%6.5f" );
    m_GenGroup.AddSlider( m_GenWidthSlider, "Width", 10, "%6.5f" );
    m_GenGroup.AddYGap();
    m_GenGroup.AddSlider( m_GenMaxWidthLocSlider, "MaxWLoc", 1, "%6.5f" );
    m_GenGroup.AddSlider( m_GenCornerRadSlider, "CornerRad", 1, "%6.5f" );
    m_GenGroup.AddYGap();
    m_GenGroup.AddSlider( m_GenTopTanAngleSlider, "TopTanAng", 90, "%7.5f" );
    m_GenGroup.AddSlider( m_GenBotTanAngleSlider, "BotTanAng", 90, "%7.5f" );
    m_GenGroup.AddYGap();
    m_GenGroup.AddSlider( m_GenTopStrSlider, "TopStr", 1, "%7.5f" );
    m_GenGroup.AddSlider( m_GenBotStrSlider, "BotStr", 1, "%7.5f" );
    m_GenGroup.AddSlider( m_GenUpStrSlider, "UpStr", 1, "%7.5f" );
    m_GenGroup.AddSlider( m_GenLowStrSlider, "LowStr", 1, "%7.5f" );

    //==== Four Series AF ====//
    m_FourSeriesGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_FourSeriesGroup.SetY( start_y );
    m_FourSeriesGroup.AddYGap();
    m_FourSeriesGroup.AddOutput( m_FourNameOutput, "Name" );
    m_FourSeriesGroup.AddYGap();
    m_FourSeriesGroup.AddSlider( m_FourChordSlider, "Chord", 10, "%7.3f" );
    m_FourSeriesGroup.AddSlider( m_FourThickChordSlider, "T/C", 1, "%7.5f" );
    m_FourSeriesGroup.AddYGap();
    m_FourSeriesGroup.AddSlider( m_FourCamberSlider, "Camber", 0.2, "%7.5f" );
    m_FourSeriesGroup.AddSlider( m_FourCamberLocSlider, "CamberLoc", 1, "%7.5f" );
    m_FourSeriesGroup.AddYGap();
    m_FourSeriesGroup.AddButton( m_FourInvertButton, "Invert Airfoil" );

    //==== Six Series AF ====//
    m_SixSeriesGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_SixSeriesGroup.SetY( start_y );
    m_SixSeriesGroup.AddYGap();
    m_SixSeriesGroup.AddOutput( m_SixNameOutput, "Name" );
    m_SixSeriesGroup.AddYGap();

    m_SixSeriesChoice.AddItem( "63" );
    m_SixSeriesChoice.AddItem( "64" );
    m_SixSeriesChoice.AddItem( "65" );
    m_SixSeriesChoice.AddItem( "66" );
    m_SixSeriesChoice.AddItem( "67" );
    m_SixSeriesChoice.AddItem( "63a" );
    m_SixSeriesChoice.AddItem( "64a" );
    m_SixSeriesChoice.AddItem( "65a" );
    m_SixSeriesGroup.AddChoice( m_SixSeriesChoice, "Series" );

    m_SixSeriesGroup.AddYGap();

    m_SixSeriesGroup.AddSlider( m_SixChordSlider, "Chord", 10, "%7.3f" );
    m_SixSeriesGroup.AddSlider( m_SixThickChordSlider, "T/C", 1, "%7.5f" );
    m_SixSeriesGroup.AddYGap();
    m_SixSeriesGroup.AddSlider( m_SixIdealClSlider, "Ideal CL", 1, "%7.5f" );
    m_SixSeriesGroup.AddSlider( m_SixASlider, "A", 1, "%7.5f" );
    m_SixSeriesGroup.AddYGap();
    m_SixSeriesGroup.AddButton( m_SixInvertButton, "Invert Airfoil" );

    //==== Biconvex AF ====//
    m_BiconvexGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_BiconvexGroup.SetY( start_y );
    m_BiconvexGroup.AddYGap();
    m_BiconvexGroup.AddSlider( m_BiconvexChordSlider, "Chord", 10, "%7.3f" );
    m_BiconvexGroup.AddSlider( m_BiconvexThickChordSlider, "T/C", 1, "%7.5f" );

    //==== Wedge AF ====//
    m_WedgeGroup.SetGroupAndScreen(  AddSubGroup( xsec_tab, 5 ), this );
    m_WedgeGroup.SetY( start_y );
    m_WedgeGroup.AddYGap();
    m_WedgeGroup.AddSlider( m_WedgeChordSlider, "Chord", 10, "%7.3f" );
    m_WedgeGroup.AddSlider( m_WedgeThickChordSlider, "T/C", 1, "%7.5f" );
    m_WedgeGroup.AddYGap();
    m_WedgeGroup.AddSlider( m_WedgeThickLocSlider, "Thick_Loc", 1, "%7.5f" );

    //==== Fuse File ====//
    m_FuseFileGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_FuseFileGroup.SetY( start_y );
    m_FuseFileGroup.AddYGap();
    m_FuseFileGroup.AddButton( m_ReadFuseFileButton, "Read File" );
    m_FuseFileGroup.AddYGap();
    m_FuseFileGroup.AddSlider( m_FileHeightSlider, "Height", 10, "%7.3f" );
    m_FuseFileGroup.AddSlider( m_FileWidthSlider, "Width", 10, "%7.3f" );

    //==== Airfoil File ====//
    m_AfFileGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_AfFileGroup.SetY( start_y );
    m_AfFileGroup.AddYGap();
    m_AfFileGroup.AddButton( m_AfReadFileButton, "Read File" );
    m_AfFileGroup.AddYGap();
    m_AfFileGroup.AddOutput( m_AfFileNameOutput, "Name" );
    m_AfFileGroup.AddYGap();
    m_AfFileGroup.AddSlider( m_AfFileChordSlider, "Chord", 10, "%7.3f" );
    m_AfFileGroup.AddYGap();
    m_AfFileGroup.AddButton( m_AfFileInvertButton, "Invert Airfoil" );

    //==== CST Airfoil ====//
    m_CSTAirfoilGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_CSTAirfoilGroup.SetY( start_y );
    m_CSTAirfoilGroup.AddYGap();
    m_CSTAirfoilGroup.AddButton( m_CSTContLERadButton, "Enforce Continuous LE Radius" );
    m_CSTAirfoilGroup.AddButton( m_CSTInvertButton, "Invert Airfoil" );
    m_CSTAirfoilGroup.AddButton( m_CSTEqArcLenButton, "Equal Arc Length Parameterization" );

    m_CSTAirfoilGroup.AddYGap();
    m_CSTAirfoilGroup.AddSlider( m_CSTChordSlider, "Chord", 10, "%7.3f");

    m_CSTAirfoilGroup.AddYGap();
    m_CSTAirfoilGroup.AddDividerBox( "Upper Surface" );

    m_CSTAirfoilGroup.SetSameLineFlag( true );
    m_CSTAirfoilGroup.SetFitWidthFlag( true );

    m_CSTAirfoilGroup.AddOutput( m_UpDegreeOutput, "Degree", m_CSTAirfoilGroup.GetButtonWidth() * 2 );
    m_CSTAirfoilGroup.SetFitWidthFlag( false );
    m_CSTAirfoilGroup.AddButton( m_UpDemoteButton, "Demote" );
    m_CSTAirfoilGroup.AddButton( m_UpPromoteButton, "Promote" );

    m_CSTAirfoilGroup.ForceNewLine();

    m_CSTAirfoilGroup.SetSameLineFlag( false );
    m_CSTAirfoilGroup.SetFitWidthFlag( true );

    m_CSTUpCoeffScroll = m_CSTAirfoilGroup.AddFlScroll( 60 );

    m_CSTUpCoeffScroll->type( Fl_Scroll::VERTICAL_ALWAYS );
    m_CSTUpCoeffScroll->box( FL_BORDER_BOX );
    m_CSTUpCoeffLayout.SetGroupAndScreen( m_CSTUpCoeffScroll, this );

    m_CSTAirfoilGroup.AddYGap();

    m_CSTAirfoilGroup.AddDividerBox( "Lower Surface" );

    m_CSTAirfoilGroup.SetSameLineFlag( true );
    m_CSTAirfoilGroup.SetFitWidthFlag( true );

    m_CSTAirfoilGroup.AddOutput( m_LowDegreeOutput, "Degree", m_CSTAirfoilGroup.GetButtonWidth() * 2 );
    m_CSTAirfoilGroup.SetFitWidthFlag( false );
    m_CSTAirfoilGroup.AddButton( m_LowDemoteButton, "Demote" );
    m_CSTAirfoilGroup.AddButton( m_LowPromoteButton, "Promote" );

    m_CSTAirfoilGroup.ForceNewLine();

    m_CSTAirfoilGroup.SetSameLineFlag( false );
    m_CSTAirfoilGroup.SetFitWidthFlag( true );

    m_CSTLowCoeffScroll = m_CSTAirfoilGroup.AddFlScroll( 60 );
    m_CSTLowCoeffScroll->type( Fl_Scroll::VERTICAL_ALWAYS );
    m_CSTLowCoeffScroll->box( FL_BORDER_BOX );
    m_CSTLowCoeffLayout.SetGroupAndScreen( m_CSTLowCoeffScroll, this );

    //==== VKT AF ====//
    m_VKTGroup.SetGroupAndScreen( AddSubGroup( xsec_tab, 5 ), this );
    m_VKTGroup.SetY( start_y );
    m_VKTGroup.AddYGap();
    m_VKTGroup.AddSlider( m_VKTChordSlider, "Chord", 10, "%7.3f" );
    m_VKTGroup.AddYGap();
    m_VKTGroup.AddSlider( m_VKTEpsilonSlider, "Epsilon", 1, "%7.5f" );
    m_VKTGroup.AddSlider( m_VKTKappaSlider, "Kappa", 1, "%7.5f" );
    m_VKTGroup.AddSlider( m_VKTTauSlider, "Tau", 10, "%7.5f" );

    DisplayGroup( &m_PointGroup );

    //==== Modify ====//

    Fl_Group* modify_tab = AddTab( "Modify" );
    Fl_Group* modify_group = AddSubGroup( modify_tab, 5 );

    m_ModifyLayout.SetButtonWidth( 70 );

    m_ModifyLayout.SetGroupAndScreen( modify_group, this );
    m_ModifyLayout.AddDividerBox( "Airfoil Section" );

    m_ModifyLayout.AddYGap();

    m_ModifyLayout.InitWidthHeightVals();
    m_ModifyLayout.AddDividerBox( "Shift, Rotate, & Scale" );

    m_ModifyLayout.AddSlider( m_AFDeltaXSlider, "Delta X/C", 1, "%7.3f" );
    m_ModifyLayout.AddSlider( m_AFDeltaYSlider, "Delta Y/C", 1, "%7.3f" );
    m_ModifyLayout.AddSlider( m_AFThetaSlider, "Theta", 20, "%7.3f" );
    m_ModifyLayout.AddSlider( m_AFScaleSlider, "Scale", 1, "%7.3f" );
    m_ModifyLayout.AddSlider( m_AFShiftLESlider, "Shift LE", 1, "%7.3f" );

    m_ModifyLayout.SetChoiceButtonWidth( 74 );

    m_ModifyLayout.AddYGap();

    m_ModifyLayout.AddDividerBox( "Leading Edge" );
    m_LECapChoice.AddItem( "FLAT" );
    m_LECapChoice.AddItem( "ROUND" );
    m_LECapChoice.AddItem( "EDGE" );
    m_LECapChoice.AddItem( "SHARP" );
    m_LECapChoice.SetOffset( vsp::FLAT_END_CAP );

    m_ModifyLayout.AddChoice( m_LECapChoice, "Cap" );

    m_ModifyLayout.AddSlider( m_LECapLengthSlider, "Length", 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_LECapOffsetSlider, "Offset", 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_LECapStrengthSlider, "Strength", 10.0, "%6.5f" );

    m_LECloseChoice.AddItem( "NONE" );
    m_LECloseChoice.AddItem( "SKEW LOWER" );
    m_LECloseChoice.AddItem( "SKEW UPPER" );
    m_LECloseChoice.AddItem( "SKEW BOTH" );

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( true );

    m_ModifyLayout.AddYGap();

    m_ModifyLayout.AddChoice( m_LECloseChoice, "Closure:", m_ModifyLayout.GetButtonWidth() * 2 );

    m_ModifyLayout.SetFitWidthFlag( false );
    m_ModifyLayout.AddButton( m_LECloseABSButton, "Abs" );
    m_ModifyLayout.AddButton( m_LECloseRELButton, "Rel" );

    m_LECloseGroup.Init( this );
    m_LECloseGroup.AddButton( m_LECloseABSButton.GetFlButton() );
    m_LECloseGroup.AddButton( m_LECloseRELButton.GetFlButton() );

    vector< int > close_val_map;
    close_val_map.push_back( vsp::ABS );
    close_val_map.push_back( vsp::REL );
    m_LECloseGroup.SetValMapVec( close_val_map );

    m_ModifyLayout.ForceNewLine();

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( false );

    m_ModifyLayout.AddSlider( m_CloseLEThickSlider, "T", 10.0, "%6.5f" );

    m_ModifyLayout.AddYGap();

    m_LETrimChoice.AddItem( "NONE" );
    m_LETrimChoice.AddItem( "X" );
    m_LETrimChoice.AddItem( "THICK" );

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( true );

    m_ModifyLayout.AddChoice( m_LETrimChoice, "Trim:", m_ModifyLayout.GetButtonWidth() * 2 );

    m_ModifyLayout.SetFitWidthFlag( false );
    m_ModifyLayout.AddButton( m_LETrimABSButton, "Abs" );
    m_ModifyLayout.AddButton( m_LETrimRELButton, "Rel" );

    m_LETrimGroup.Init( this );
    m_LETrimGroup.AddButton( m_LETrimABSButton.GetFlButton() );
    m_LETrimGroup.AddButton( m_LETrimRELButton.GetFlButton() );

    vector< int > trim_val_map;
    trim_val_map.push_back( vsp::ABS );
    trim_val_map.push_back( vsp::REL );
    m_LETrimGroup.SetValMapVec( trim_val_map );

    m_ModifyLayout.ForceNewLine();

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( false );

    m_ModifyLayout.AddSlider( m_TrimLEXSlider, "X", 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_TrimLEThickSlider, "T", 10.0, "%6.5f" );

    m_ModifyLayout.AddYGap();

    m_ModifyLayout.AddDividerBox( "Trailing Edge" );
    m_TECapChoice.AddItem( "FLAT" );
    m_TECapChoice.AddItem( "ROUND" );
    m_TECapChoice.AddItem( "EDGE" );
    m_TECapChoice.AddItem( "SHARP" );
    m_TECapChoice.SetOffset( vsp::FLAT_END_CAP );

    m_ModifyLayout.AddChoice( m_TECapChoice, "Cap:" );

    m_ModifyLayout.AddSlider( m_TECapLengthSlider, "Length", 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_TECapOffsetSlider, "Offset", 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_TECapStrengthSlider, "Strength", 10.0, "%6.5f" );

    m_TECloseChoice.AddItem( "NONE" );
    m_TECloseChoice.AddItem( "SKEW LOWER" );
    m_TECloseChoice.AddItem( "SKEW UPPER" );
    m_TECloseChoice.AddItem( "SKEW BOTH" );
    m_TECloseChoice.AddItem( "EXTRAPOLATE" );

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( true );

    m_ModifyLayout.AddYGap();

    m_ModifyLayout.AddChoice( m_TECloseChoice, "Closure:", m_ModifyLayout.GetButtonWidth() * 2 );

    m_ModifyLayout.SetFitWidthFlag( false );
    m_ModifyLayout.AddButton( m_TECloseABSButton, "Abs" );
    m_ModifyLayout.AddButton( m_TECloseRELButton, "Rel" );

    m_TECloseGroup.Init( this );
    m_TECloseGroup.AddButton( m_TECloseABSButton.GetFlButton() );
    m_TECloseGroup.AddButton( m_TECloseRELButton.GetFlButton() );

    m_TECloseGroup.SetValMapVec( close_val_map );

    m_ModifyLayout.ForceNewLine();

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( false );

    m_ModifyLayout.AddSlider( m_CloseTEThickSlider, "T", 10.0, "%6.5f" );

    m_ModifyLayout.AddYGap();

    m_TETrimChoice.AddItem( "NONE" );
    m_TETrimChoice.AddItem( "X" );
    m_TETrimChoice.AddItem( "THICK" );

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( true );

    m_ModifyLayout.AddChoice( m_TETrimChoice, "Trim:", m_ModifyLayout.GetButtonWidth() * 2 );

    m_ModifyLayout.SetFitWidthFlag( false );
    m_ModifyLayout.AddButton( m_TETrimABSButton, "Abs" );
    m_ModifyLayout.AddButton( m_TETrimRELButton, "Rel" );

    m_TETrimGroup.Init( this );
    m_TETrimGroup.AddButton( m_TETrimABSButton.GetFlButton() );
    m_TETrimGroup.AddButton( m_TETrimRELButton.GetFlButton() );

    m_TETrimGroup.SetValMapVec( trim_val_map );

    m_ModifyLayout.ForceNewLine();

    m_ModifyLayout.SetFitWidthFlag( true );
    m_ModifyLayout.SetSameLineFlag( false );

    m_ModifyLayout.AddSlider( m_TrimTEXSlider, "X", 10.0, "%6.5f" );
    m_ModifyLayout.AddSlider( m_TrimTEThickSlider, "T", 10.0, "%6.5f" );

}


//==== Show BOR Screen ====//
void BORScreen::Show()
{
    if ( Update() )
    {
        m_FLTK_Window->show();
    }
}

//==== Update BOR Screen ====//
bool BORScreen::Update()
{
    assert( m_ScreenMgr );

    Geom* geom_ptr = m_ScreenMgr->GetCurrGeom();
    if ( !geom_ptr || geom_ptr->GetType().m_Type != BOR_GEOM_TYPE )
    {
        Hide();
        return false;
    }

    GeomScreen::Update();

    //==== Update BOR Specific Parms ====//
    BORGeom* bor_ptr = dynamic_cast< BORGeom* >( geom_ptr );
    assert( bor_ptr );

    m_ModeChoice.Update( bor_ptr->m_Mode.GetID() );

    m_BORDiameterSlider.Update( bor_ptr->m_Diameter.GetID() );
    m_AngleSlider.Update( bor_ptr->m_Angle.GetID() );

    if ( bor_ptr->m_Mode() == vsp::BOR_FLOWTHROUGH )
    {
        m_BORDiameterSlider.Activate();
        m_AngleSlider.Activate();
    }
    else
    {
        m_BORDiameterSlider.Deactivate();
        m_AngleSlider.Deactivate();
    }

    m_LEClusterSlider.Update( bor_ptr->m_LECluster.GetID() );
    m_TEClusterSlider.Update( bor_ptr->m_TECluster.GetID() );

    m_CapTessSlider.Update( bor_ptr->m_CapUMinTess.GetID() );

    XSecCurve* xsc = bor_ptr->GetXSecCurve();
    if ( xsc )
    {
        m_XSecTypeChoice.SetVal( xsc->GetType() );

        if ( xsc->GetType() == vsp::XS_POINT )
        {
            DisplayGroup( NULL );
        }
        else if ( xsc->GetType() == vsp::XS_SUPER_ELLIPSE )
        {
            DisplayGroup( &m_SuperGroup );

            SuperXSec* super_xs = dynamic_cast< SuperXSec* >( xsc );
            assert( super_xs );
            m_SuperHeightSlider.Update( super_xs->m_Height.GetID() );
            m_SuperWidthSlider.Update( super_xs->m_Width.GetID() );
            m_SuperMSlider.Update( super_xs->m_M.GetID() );
            m_SuperNSlider.Update( super_xs->m_N.GetID() );
            m_SuperToggleSym.Update( super_xs->m_TopBotSym.GetID() );
            m_SuperM_botSlider.Update( super_xs->m_M_bot.GetID() );
            m_SuperN_botSlider.Update( super_xs->m_N_bot.GetID() );
            m_SuperMaxWidthLocSlider.Update( super_xs->m_MaxWidthLoc.GetID() );

            if ( super_xs->m_TopBotSym() )
            {
                m_SuperM_botSlider.Deactivate();
                m_SuperN_botSlider.Deactivate();
            }
            else if ( !super_xs->m_TopBotSym() )
            {
                m_SuperM_botSlider.Activate();
                m_SuperN_botSlider.Activate();
            }
        }
        else if ( xsc->GetType() == vsp::XS_CIRCLE )
        {
            DisplayGroup( &m_CircleGroup );
            CircleXSec* circle_xs = dynamic_cast< CircleXSec* >( xsc );
            assert( circle_xs );

            m_DiameterSlider.Update( circle_xs->m_Diameter.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_ELLIPSE )
        {
            DisplayGroup( & m_EllipseGroup );

            EllipseXSec* ellipse_xs = dynamic_cast< EllipseXSec* >( xsc );
            m_EllipseHeightSlider.Update( ellipse_xs->m_Height.GetID() );
            m_EllipseWidthSlider.Update( ellipse_xs->m_Width.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_ROUNDED_RECTANGLE )
        {
            DisplayGroup( & m_RoundedRectGroup );
            RoundedRectXSec* rect_xs = dynamic_cast< RoundedRectXSec* >( xsc );
            assert( rect_xs );

            m_RRHeightSlider.Update( rect_xs->m_Height.GetID() );
            m_RRWidthSlider.Update( rect_xs->m_Width.GetID() );
            m_RRRadiusSlider.Update( rect_xs->m_Radius.GetID() );
            m_RRKeyCornerButton.Update( rect_xs->m_KeyCornerParm.GetID() );
            m_RRSkewSlider.Update( rect_xs->m_Skew.GetID() );
            m_RRKeystoneSlider.Update( rect_xs->m_Keystone.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_GENERAL_FUSE )
        {
            DisplayGroup( &m_GenGroup );
            GeneralFuseXSec* gen_xs = dynamic_cast< GeneralFuseXSec* >( xsc );
            assert( gen_xs );

            m_GenHeightSlider.Update( gen_xs->m_Height.GetID() );
            m_GenWidthSlider.Update( gen_xs->m_Width.GetID() );
            m_GenMaxWidthLocSlider.Update( gen_xs->m_MaxWidthLoc.GetID() );
            m_GenCornerRadSlider.Update( gen_xs->m_CornerRad.GetID() );
            m_GenTopTanAngleSlider.Update( gen_xs->m_TopTanAngle.GetID() );
            m_GenBotTanAngleSlider.Update( gen_xs->m_BotTanAngle.GetID() );
            m_GenTopStrSlider.Update( gen_xs->m_TopStr.GetID() );
            m_GenBotStrSlider.Update( gen_xs->m_BotStr.GetID() );
            m_GenUpStrSlider.Update( gen_xs->m_UpStr.GetID() );
            m_GenLowStrSlider.Update( gen_xs->m_LowStr.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_FOUR_SERIES )
        {
            DisplayGroup( &m_FourSeriesGroup );
            FourSeries* fs_xs = dynamic_cast< FourSeries* >( xsc );
            assert( fs_xs );

            m_FourChordSlider.Update( fs_xs->m_Chord.GetID() );
            m_FourThickChordSlider.Update( fs_xs->m_ThickChord.GetID() );
            m_FourCamberSlider.Update( fs_xs->m_Camber.GetID() );
            m_FourCamberLocSlider.Update( fs_xs->m_CamberLoc.GetID() );
            m_FourInvertButton.Update( fs_xs->m_Invert.GetID() );
            m_FourNameOutput.Update( fs_xs->GetAirfoilName() );
        }
        else if ( xsc->GetType() == vsp::XS_SIX_SERIES )
        {
            DisplayGroup( &m_SixSeriesGroup );
            SixSeries* ss_xs = dynamic_cast< SixSeries* >( xsc );
            assert( ss_xs );

            m_SixChordSlider.Update( ss_xs->m_Chord.GetID() );
            m_SixThickChordSlider.Update( ss_xs->m_ThickChord.GetID() );
            m_SixIdealClSlider.Update( ss_xs->m_IdealCl.GetID() );
            m_SixASlider.Update( ss_xs->m_A.GetID() );

            m_SixInvertButton.Update( ss_xs->m_Invert.GetID() );
            m_SixNameOutput.Update( ss_xs->GetAirfoilName() );
            m_SixSeriesChoice.Update( ss_xs->m_Series.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_BICONVEX )
        {
            DisplayGroup( &m_BiconvexGroup );
            Biconvex* bi_xs = dynamic_cast< Biconvex* >( xsc );
            assert( bi_xs );

            m_BiconvexChordSlider.Update( bi_xs->m_Chord.GetID() );
            m_BiconvexThickChordSlider.Update( bi_xs->m_ThickChord.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_WEDGE )
        {
            DisplayGroup( &m_WedgeGroup );
            Wedge* we_xs = dynamic_cast< Wedge* >( xsc );
            assert( we_xs );

            m_WedgeChordSlider.Update( we_xs->m_Chord.GetID() );
            m_WedgeThickChordSlider.Update( we_xs->m_ThickChord.GetID() );
            m_WedgeThickLocSlider.Update( we_xs->m_ThickLoc.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_FILE_FUSE )
        {
            DisplayGroup( &m_FuseFileGroup );
            FileXSec* file_xs = dynamic_cast< FileXSec* >( xsc );
            assert( file_xs );
            m_FileHeightSlider.Update( file_xs->m_Height.GetID() );
            m_FileWidthSlider.Update( file_xs->m_Width.GetID() );
        }
        else if ( xsc->GetType() == vsp::XS_FILE_AIRFOIL )
        {
            DisplayGroup( &m_AfFileGroup );
            FileAirfoil* affile_xs = dynamic_cast< FileAirfoil* >( xsc );
            assert( affile_xs );

            m_AfFileChordSlider.Update( affile_xs->m_Chord.GetID() );
            m_AfFileInvertButton.Update( affile_xs->m_Invert.GetID() );
            m_AfFileNameOutput.Update( affile_xs->GetAirfoilName() );
        }
        else if ( xsc->GetType() == vsp::XS_CST_AIRFOIL )
        {
            DisplayGroup( &m_CSTAirfoilGroup );
            CSTAirfoil* cst_xs = dynamic_cast< CSTAirfoil* >( xsc );
            assert( cst_xs );

            int num_up = cst_xs->m_UpDeg() + 1;
            int num_low = cst_xs->m_LowDeg() + 1;

            char str[255];
            sprintf( str, "%d", cst_xs->m_UpDeg() );
            m_UpDegreeOutput.Update( str );
            sprintf( str, "%d", cst_xs->m_LowDeg() );
            m_LowDegreeOutput.Update( str );

            m_CSTChordSlider.Update(cst_xs->m_Chord.GetID());
            m_CSTInvertButton.Update( cst_xs->m_Invert.GetID() );
            m_CSTContLERadButton.Update( cst_xs->m_ContLERad.GetID() );
            m_CSTEqArcLenButton.Update( cst_xs->m_EqArcLen.GetID() );

            if ( ( m_UpCoeffSliderVec.size() != num_up ) || ( m_LowCoeffSliderVec.size() != num_low ) )
            {
                RebuildCSTGroup( cst_xs );
            }

            for ( int i = 0; i < num_up; i++ )
            {
                Parm *p = cst_xs->m_UpCoeffParmVec[i];
                if ( p )
                {
                    m_UpCoeffSliderVec[i].Update( p->GetID() );
                }
            }

            for ( int i = 0; i < num_low; i++ )
            {
                Parm *p = cst_xs->m_LowCoeffParmVec[i];
                if ( p )
                {
                    m_LowCoeffSliderVec[i].Update( p->GetID() );
                }
            }

            if ( cst_xs->m_ContLERad() && num_low > 0 )
            {
                m_LowCoeffSliderVec[0].Deactivate();
            }
        }
        else if ( xsc->GetType() == vsp::XS_VKT_AIRFOIL )
        {
            DisplayGroup( &m_VKTGroup );
            VKTAirfoil* vkt_xs = dynamic_cast< VKTAirfoil* >( xsc );
            assert( vkt_xs );

            m_VKTChordSlider.Update( vkt_xs->m_Chord.GetID() );
            m_VKTEpsilonSlider.Update( vkt_xs->m_Epsilon.GetID() );
            m_VKTKappaSlider.Update( vkt_xs->m_Kappa.GetID() );
            m_VKTTauSlider.Update( vkt_xs->m_Tau.GetID() );
        }

        m_TECloseChoice.Update( xsc->m_TECloseType.GetID() );
        m_TECloseGroup.Update( xsc->m_TECloseAbsRel.GetID() );

        if ( xsc->m_TECloseType() != vsp::CLOSE_NONE )
        {
            m_TECloseABSButton.Activate();
            m_TECloseRELButton.Activate();
            m_CloseTEThickSlider.Activate();

            if ( xsc->m_TECloseAbsRel() == vsp::ABS )
            {
                xsc->m_TECloseThick.Activate();
                xsc->m_TECloseThickChord.Deactivate();
            }
            else
            {
                xsc->m_TECloseThick.Deactivate();
                xsc->m_TECloseThickChord.Activate();
            }
        }
        else
        {
            m_TECloseABSButton.Deactivate();
            m_TECloseRELButton.Deactivate();
            m_CloseTEThickSlider.Deactivate();
            xsc->m_TECloseThick.Deactivate();
            xsc->m_TECloseThickChord.Deactivate();
        }

        if ( xsc->m_TECloseAbsRel() == vsp::ABS )
        {
            m_CloseTEThickSlider.Update( 1, xsc->m_TECloseThick.GetID(), xsc->m_TECloseThickChord.GetID() );
        }
        else
        {
            m_CloseTEThickSlider.Update( 2, xsc->m_TECloseThick.GetID(), xsc->m_TECloseThickChord.GetID() );
        }

        m_LECloseChoice.Update( xsc->m_LECloseType.GetID() );
        m_LECloseGroup.Update( xsc->m_LECloseAbsRel.GetID() );

        if ( xsc->m_LECloseType() != vsp::CLOSE_NONE )
        {
            m_LECloseABSButton.Activate();
            m_LECloseRELButton.Activate();
            m_CloseLEThickSlider.Activate();

            if ( xsc->m_LECloseAbsRel() == vsp::ABS )
            {
                xsc->m_LECloseThick.Activate();
                xsc->m_LECloseThickChord.Deactivate();
            }
            else
            {
                xsc->m_LECloseThick.Deactivate();
                xsc->m_LECloseThickChord.Activate();
            }
        }
        else
        {
            m_LECloseABSButton.Deactivate();
            m_LECloseRELButton.Deactivate();
            m_CloseLEThickSlider.Deactivate();
            xsc->m_LECloseThick.Deactivate();
            xsc->m_LECloseThickChord.Deactivate();
        }

        if ( xsc->m_LECloseAbsRel() == vsp::ABS )
        {
            m_CloseLEThickSlider.Update( 1, xsc->m_LECloseThick.GetID(), xsc->m_LECloseThickChord.GetID() );
        }
        else
        {
            m_CloseLEThickSlider.Update( 2, xsc->m_LECloseThick.GetID(), xsc->m_LECloseThickChord.GetID() );
        }

        m_TETrimChoice.Update( xsc->m_TETrimType.GetID() );
        m_TETrimGroup.Update( xsc->m_TETrimAbsRel.GetID() );

        m_TrimTEXSlider.Deactivate();
        m_TrimTEThickSlider.Deactivate();
        m_TETrimABSButton.Deactivate();
        m_TETrimRELButton.Deactivate();

        xsc->m_TETrimX.Deactivate();
        xsc->m_TETrimXChord.Deactivate();
        xsc->m_TETrimThickChord.Deactivate();
        xsc->m_TETrimThick.Deactivate();

        if ( xsc->m_TETrimType() != vsp::TRIM_NONE )
        {
            m_TETrimABSButton.Activate();
            m_TETrimRELButton.Activate();
        }

        if ( xsc->m_TETrimType() == vsp::TRIM_X )
        {
            if ( xsc->m_TETrimAbsRel() == vsp::ABS )
            {
                xsc->m_TETrimX.Activate();
            }
            else
            {
                xsc->m_TETrimXChord.Activate();
            }
        }
        else if ( xsc->m_TETrimType() == vsp::TRIM_THICK )
        {
            if ( xsc->m_TETrimAbsRel() == vsp::ABS )
            {
                xsc->m_TETrimThick.Activate();
            }
            else
            {
                xsc->m_TETrimThickChord.Activate();
            }
        }

        if ( xsc->m_TETrimAbsRel() == vsp::ABS )
        {
            m_TrimTEXSlider.Update( 1, xsc->m_TETrimX.GetID(), xsc->m_TETrimXChord.GetID() );
            m_TrimTEThickSlider.Update( 1, xsc->m_TETrimThick.GetID(), xsc->m_TETrimThickChord.GetID() );
        }
        else
        {
            m_TrimTEXSlider.Update( 2, xsc->m_TETrimX.GetID(), xsc->m_TETrimXChord.GetID() );
            m_TrimTEThickSlider.Update( 2, xsc->m_TETrimThick.GetID(), xsc->m_TETrimThickChord.GetID() );
        }

        m_LETrimChoice.Update( xsc->m_LETrimType.GetID() );
        m_LETrimGroup.Update( xsc->m_LETrimAbsRel.GetID() );

        m_TrimLEXSlider.Deactivate();
        m_TrimLEThickSlider.Deactivate();
        m_LETrimABSButton.Deactivate();
        m_LETrimRELButton.Deactivate();

        xsc->m_LETrimX.Deactivate();
        xsc->m_LETrimXChord.Deactivate();
        xsc->m_LETrimThickChord.Deactivate();
        xsc->m_LETrimThick.Deactivate();

        if ( xsc->m_LETrimType() != vsp::TRIM_NONE )
        {
            m_LETrimABSButton.Activate();
            m_LETrimRELButton.Activate();
        }

        if ( xsc->m_LETrimType() == vsp::TRIM_X )
        {
            if ( xsc->m_LETrimAbsRel() == vsp::ABS )
            {
                xsc->m_LETrimX.Activate();
            }
            else
            {
                xsc->m_LETrimXChord.Activate();
            }
        }
        else if ( xsc->m_LETrimType() == vsp::TRIM_THICK )
        {
            if ( xsc->m_LETrimAbsRel() == vsp::ABS )
            {
                xsc->m_LETrimThick.Activate();
            }
            else
            {
                xsc->m_LETrimThickChord.Activate();
            }
        }

        if ( xsc->m_LETrimAbsRel() == vsp::ABS )
        {
            m_TrimLEXSlider.Update( 1, xsc->m_LETrimX.GetID(), xsc->m_LETrimXChord.GetID() );
            m_TrimLEThickSlider.Update( 1, xsc->m_LETrimThick.GetID(), xsc->m_LETrimThickChord.GetID() );
        }
        else
        {
            m_TrimLEXSlider.Update( 2, xsc->m_LETrimX.GetID(), xsc->m_LETrimXChord.GetID() );
            m_TrimLEThickSlider.Update( 2, xsc->m_LETrimThick.GetID(), xsc->m_LETrimThickChord.GetID() );
        }

        m_TECapChoice.Update( xsc->m_TECapType.GetID() );

        m_TECapLengthSlider.Update( xsc->m_TECapLength.GetID() );
        m_TECapOffsetSlider.Update( xsc->m_TECapOffset.GetID() );
        m_TECapStrengthSlider.Update( xsc->m_TECapStrength.GetID() );

        m_TECapLengthSlider.Deactivate();
        m_TECapOffsetSlider.Deactivate();
        m_TECapStrengthSlider.Deactivate();

        switch( xsc->m_TECapType() ){
            case vsp::FLAT_END_CAP:
                break;
            case vsp::ROUND_END_CAP:
                m_TECapLengthSlider.Activate();
                m_TECapOffsetSlider.Activate();
                break;
            case vsp::EDGE_END_CAP:
                m_TECapLengthSlider.Activate();
                m_TECapOffsetSlider.Activate();
                break;
            case vsp::SHARP_END_CAP:
                m_TECapLengthSlider.Activate();
                m_TECapOffsetSlider.Activate();
                m_TECapStrengthSlider.Activate();
                break;
        }

        m_LECapChoice.Update( xsc->m_LECapType.GetID() );

        m_LECapLengthSlider.Update( xsc->m_LECapLength.GetID() );
        m_LECapOffsetSlider.Update( xsc->m_LECapOffset.GetID() );
        m_LECapStrengthSlider.Update( xsc->m_LECapStrength.GetID() );

        m_LECapLengthSlider.Deactivate();
        m_LECapOffsetSlider.Deactivate();
        m_LECapStrengthSlider.Deactivate();

        switch( xsc->m_LECapType() ){
            case vsp::FLAT_END_CAP:
                break;
            case vsp::ROUND_END_CAP:
                m_LECapLengthSlider.Activate();
                m_LECapOffsetSlider.Activate();
                break;
            case vsp::EDGE_END_CAP:
                m_LECapLengthSlider.Activate();
                m_LECapOffsetSlider.Activate();
                break;
            case vsp::SHARP_END_CAP:
                m_LECapLengthSlider.Activate();
                m_LECapOffsetSlider.Activate();
                m_LECapStrengthSlider.Activate();
                break;
        }

        m_AFThetaSlider.Update( xsc->m_Theta.GetID() );
        m_AFScaleSlider.Update( xsc->m_Scale.GetID() );
        m_AFDeltaXSlider.Update( xsc->m_DeltaX.GetID() );
        m_AFDeltaYSlider.Update( xsc->m_DeltaY.GetID() );
        m_AFShiftLESlider.Update( xsc->m_ShiftLE.GetID() );

    }

    return true;
}

void BORScreen::GuiDeviceCallBack( GuiDevice* gui_device )
{
    //==== Find BOR Ptr ====//
    Geom *geom_ptr = m_ScreenMgr->GetCurrGeom();
    if ( !geom_ptr || geom_ptr->GetType().m_Type != BOR_GEOM_TYPE )
    {
        return;
    }
    BORGeom *bor_ptr = dynamic_cast< BORGeom * >( geom_ptr );
    assert( bor_ptr );

    if (gui_device == &m_XSecTypeChoice)
    {
        int t = m_XSecTypeChoice.GetVal();
        bor_ptr->SetXSecCurveType( t );
    }
    else if ( gui_device == &m_ShowXSecButton )
    {
        m_ScreenMgr->ShowScreen( ScreenMgr::VSP_XSEC_SCREEN );
    }

    GeomScreen::GuiDeviceCallBack( gui_device );
}

//==== Non Menu Callbacks ====//
void BORScreen::CallBack( Fl_Widget *w )
{
    GeomScreen::CallBack( w );
}

void BORScreen::DisplayGroup( GroupLayout* group )
{
    if ( m_CurrDisplayGroup == group )
    {
        return;
    }

    m_SuperGroup.Hide();
    m_CircleGroup.Hide();
    m_EllipseGroup.Hide();
    m_RoundedRectGroup.Hide();
    m_GenGroup.Hide();
    m_FourSeriesGroup.Hide();
    m_SixSeriesGroup.Hide();
    m_BiconvexGroup.Hide();
    m_WedgeGroup.Hide();
    m_FuseFileGroup.Hide();
    m_AfFileGroup.Hide();
    m_CSTAirfoilGroup.Hide();
    m_VKTGroup.Hide();

    m_CurrDisplayGroup = group;

    if ( group )
    {
        group->Show();
    }
}


void BORScreen::RebuildCSTGroup( CSTAirfoil* cst_xs)
{
    if ( !cst_xs )
    {
        return;
    }

    if ( !m_CSTUpCoeffScroll || !m_CSTLowCoeffScroll )
    {
        return;
    }

    m_CSTUpCoeffScroll->clear();
    m_CSTUpCoeffLayout.SetGroup( m_CSTUpCoeffScroll );
    m_CSTUpCoeffLayout.InitWidthHeightVals();

    m_UpCoeffSliderVec.clear();

    int num_up = cst_xs->m_UpDeg() + 1;

    m_UpCoeffSliderVec.resize( num_up );

    for ( int i = 0; i < num_up; i++ )
    {
        m_CSTUpCoeffLayout.AddSlider( m_UpCoeffSliderVec[i], "AUTO_UPDATE", 2, "%9.5f" );
    }




    m_CSTLowCoeffScroll->clear();
    m_CSTLowCoeffLayout.SetGroup( m_CSTLowCoeffScroll );
    m_CSTLowCoeffLayout.InitWidthHeightVals();

    m_LowCoeffSliderVec.clear();

    int num_low = cst_xs->m_LowDeg() + 1;

    m_LowCoeffSliderVec.resize( num_low );


    for ( int i = 0; i < num_low; i++ )
    {
        m_CSTLowCoeffLayout.AddSlider( m_LowCoeffSliderVec[i], "AUTO_UPDATE", 2, "%9.5f" );
    }
}

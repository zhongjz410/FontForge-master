/* Copyright (C) 2007-2012 by George Williams */
/*
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:

 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.

 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.

 * The name of the author may not be used to endorse or promote products
 * derived from this software without specific prior written permission.

 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <fontforge-config.h>

#include "mathconstants.h"

#include "fontforgevw.h"
#include "fvfonts.h"
#include "splineutil.h"

#ifdef __need_size_t
/* This is a bug on the mac, someone defines this and leaves it defined */
/*  that means when I load stddef.h it only defines size_t and doesn't */
/*  do offset_of, which is what I need */
# undef __need_size_t
#endif
#include <stddef.h>

#define MCD(ui_name,name,msg,np) { ui_name, #name, offsetof(struct MATH,name), -1,msg,np }
#define MCDD(ui_name,name,devtab_name,msg,np) { ui_name, #name, offsetof(struct MATH,name), offsetof(struct MATH,devtab_name),msg,np }

struct math_constants_descriptor math_constants_descriptor[] = {
    MCD(N_("文字缩小比例:"),ScriptPercentScaleDown,N_("Percentage scale down for script level 1"),0),
    MCD(N_("文字缩小比例:"),ScriptScriptPercentScaleDown,N_("Percentage scale down for script level 2"),0),
    MCD(N_("分隔子公式最小高度:"),DelimitedSubFormulaMinHeight,N_("Minimum height at which to treat a delimited\nexpression as a subformula"),0),
    MCD(N_("显示操作员最小高度:"),DisplayOperatorMinHeight,N_("Minimum height of n-ary operators (integration, summation, etc.)"),0),
    MCDD(N_("数学边位:"),MathLeading,MathLeading_adjust,N_("White space to be left between math formulae\nto ensure proper line spacing."),0),
    MCDD(N_("轴高:"),AxisHeight,AxisHeight_adjust,N_("Axis height of the font"),0),
    MCDD(N_("上升部高:"),AccentBaseHeight,AccentBaseHeight_adjust,N_("Maximum (ink) height of accent base that\ndoes not require raising the accents."),0),
    MCDD(N_("扁平音调高度:"),FlattenedAccentBaseHeight,FlattenedAccentBaseHeight_adjust,N_("Maximum (ink) height of accent base that\ndoes not require flattening the accents."),0),
    MCDD(N_("下标下沉:"),SubscriptShiftDown,SubscriptShiftDown_adjust,N_("The standard shift down applied to subscript elements.\nPositive for moving downward."),1),
    MCDD(N_("下标上限:"),SubscriptTopMax,SubscriptTopMax_adjust,N_("Maximum height of the (ink) top of subscripts\nthat does not require moving\nsubscripts further down."),0),
    MCDD(N_("下标基线下沉最小值:"),SubscriptBaselineDropMin,SubscriptBaselineDropMin_adjust,N_("Maximum allowed drop of the baseline of\nsubscripts relative to the bottom of the base.\nUsed for bases that are treated as a box\nor extended shape. Positive for subscript\nbaseline dropped below base bottom."),0),
    MCDD(N_("上标上升:"),SuperscriptShiftUp,SuperscriptShiftUp_adjust,N_("Standard shift up applied to superscript elements."),0),
    MCDD(N_("上标移位上紧:"),SuperscriptShiftUpCramped,SuperscriptShiftUpCramped_adjust,N_("Standard shift of superscript relative\nto base in cramped mode."),0),
    MCDD(N_("上标底端最小值:"),SuperscriptBottomMin,SuperscriptBottomMin_adjust,N_("Minimum allowed height of the bottom\nof superscripts that does not require moving\nthem further up."),0),
    MCDD(N_("上标基线下降最大值:"),SuperscriptBaselineDropMax,SuperscriptBaselineDropMax_adjust,N_("Maximum allowed drop of the baseline of\nsuperscripts relative to the top of the base.\nUsed for bases that are treated as a box\nor extended shape. Positive for superscript\nbaseline below base top."),0),
    MCDD(N_("上标间隙最小值:"),SubSuperscriptGapMin,SubSuperscriptGapMin_adjust,N_("Minimum gap between the superscript and subscript ink."),0),
    MCDD(N_("带下标的上标底端最大值:"),SuperscriptBottomMaxWithSubscript,SuperscriptBottomMaxWithSubscript_adjust,N_("The maximum level to which the (ink) bottom\nof superscript can be pushed to increase the\ngap between superscript and subscript, before\nsubscript starts being moved down."),0),
    MCDD(N_("字符间距:"),SpaceAfterScript,SpaceAfterScript_adjust,N_("Extra white space to be added after each\nsub/superscript."),0),
    MCDD(N_("上限间隙最小值:"),UpperLimitGapMin,UpperLimitGapMin_adjust,N_("Minimum gap between the bottom of the\nupper limit, and the top of the base operator."),1),
    MCDD(N_("上限基线最小值:"),UpperLimitBaselineRiseMin,UpperLimitBaselineRiseMin_adjust,N_("Minimum distance between the baseline of an upper\nlimit and the bottom of the base operator."),0),
    MCDD(N_("间隙最小值下限:"),LowerLimitGapMin,LowerLimitGapMin_adjust,N_("Minimum gap between (ink) top of the lower limit,\nand (ink) bottom of the base operator."),0),
    MCDD(N_("基线最小值下限:"),LowerLimitBaselineDropMin,LowerLimitBaselineDropMin_adjust,N_("Minimum distance between the baseline of the\nlower limit and bottom of the base operator."),0),
    MCDD(N_("堆栈顶部移动:"),StackTopShiftUp,StackTopShiftUp_adjust,N_("Standard shift up applied to the top element of a stack."),1),
    MCDD(N_("堆栈顶部显示样式移动:"),StackTopDisplayStyleShiftUp,StackTopDisplayStyleShiftUp_adjust,N_("Standard shift up applied to the top element of\na stack in display style."),0),
    MCDD(N_("堆栈底部移动:"),StackBottomShiftDown,StackBottomShiftDown_adjust,N_("Standard shift down applied to the bottom element of a stack.\nPositive values indicate downward motion."),0),
    MCDD(N_("堆栈底部显示样式移动:"),StackBottomDisplayStyleShiftDown,StackBottomDisplayStyleShiftDown_adjust,N_("Standard shift down applied to the bottom\nelement of a stack in display style.\nPositive values indicate downward motion."),0),
    MCDD(N_("堆栈间隙最小值:"),StackGapMin,StackGapMin_adjust,N_("Minimum gap between bottom of the top\nelement of a stack, and the top of the bottom element."),0),
    MCDD(N_("堆栈显示样式间隙最小值:"),StackDisplayStyleGapMin,StackDisplayStyleGapMin_adjust,N_("Minimum gap between bottom of the top\nelement of a stack and the top of the bottom\nelement in display style."),0),
    MCDD(N_("拉伸堆栈顶部移动:"),StretchStackTopShiftUp,StretchStackTopShiftUp_adjust,N_("Standard shift up applied to the top element of the stretch stack."),0),
    MCDD(N_("拉伸堆栈底部移动:"),StretchStackBottomShiftDown,StretchStackBottomShiftDown_adjust,N_("Standard shift down applied to the bottom\nelement of the stretch stack.\nPositive values indicate downward motion."),0),
    MCDD(N_("拉伸堆栈间隙大于最小值:"),StretchStackGapAboveMin,StretchStackGapAboveMin_adjust,N_("Minimum gap between the ink of the stretched\nelement and the ink bottom of the element\nabove.."),0),
    MCDD(N_("拉伸堆栈间隙低于最小值:"),StretchStackGapBelowMin,StretchStackGapBelowMin_adjust,N_("Minimum gap between the ink of the stretched\nelement and the ink top of the element below."),0),
    MCDD(N_("分数分子向上移动:"),FractionNumeratorShiftUp,FractionNumeratorShiftUp_adjust,N_("Standard shift up applied to the numerator."),1),
    MCDD(N_("分数分子显示样式向上移动:"),FractionNumeratorDisplayStyleShiftUp,FractionNumeratorDisplayStyleShiftUp_adjust,N_("Standard shift up applied to the\nnumerator in display style."),0),
    MCDD(N_("分数分母向下移动:"),FractionDenominatorShiftDown,FractionDenominatorShiftDown_adjust,N_("Standard shift down applied to the denominator.\nPositive values indicate downward motion."),0),
    MCDD(N_("分数分母显示样式向下移动:"),FractionDenominatorDisplayStyleShiftDown,FractionDenominatorDisplayStyleShiftDown_adjust,N_("Standard shift down applied to the\ndenominator in display style.\nPositive values indicate downward motion."),0),
    MCDD(N_("分数分子间隙最小值:"),FractionNumeratorGapMin,FractionNumeratorGapMin_adjust,N_("Minimum tolerated gap between the ink\nbottom of the numerator and the ink of the fraction bar."),0),
    MCDD(N_("分数分子显示样式间隙最小值:"),FractionNumeratorDisplayStyleGapMin,FractionNumeratorDisplayStyleGapMin_adjust,N_("Minimum tolerated gap between the ink\nbottom of the numerator and the ink of the fraction\nbar in display style."),0),
    MCDD(N_("分形规则厚度:"),FractionRuleThickness,FractionRuleThickness_adjust,N_("Thickness of the fraction bar."),0),
    MCDD(N_("分数分母间隙最小值:"),FractionDenominatorGapMin,FractionDenominatorGapMin_adjust,N_("Minimum tolerated gap between the ink top of the denominator\nand the ink of the fraction bar.."),0),
    MCDD(N_("分数分母显示样式间隙最小值:"),FractionDenominatorDisplayStyleGapMin,FractionDenominatorDisplayStyleGapMin_adjust,N_("Minimum tolerated gap between the ink top of the denominator\nand the ink of the fraction bar in display style."),0),
    MCDD(N_("横向偏分:"),SkewedFractionHorizontalGap,SkewedFractionHorizontalGap_adjust,N_("Horizontal distance between the top\nand bottom elements of a skewed fraction."),0),
    MCDD(N_("纵向偏分:"),SkewedFractionVerticalGap,SkewedFractionVerticalGap_adjust,N_("Vertical distance between the ink of the top and\nbottom elements of a skewed fraction."),0),
    MCDD(N_("顶线垂直间隙:"),OverbarVerticalGap,OverbarVerticalGap_adjust,N_("Distance between the overbar and\nthe ink top of the base."),1),
    MCDD(N_("顶线规则厚度:"),OverbarRuleThickness,OverbarRuleThickness_adjust,N_("Thickness of the overbar."),0),
    MCDD(N_("顶线额外上升:"),OverbarExtraAscender,OverbarExtraAscender_adjust,N_("Extra white space reserved above the overbar."),0),
    MCDD(N_("底线垂直间距:"),UnderbarVerticalGap,UnderbarVerticalGap_adjust,N_("Distance between underbar and\nthe (ink) bottom of the base."),0),
    MCDD(N_("底线规则厚度:"),UnderbarRuleThickness,UnderbarRuleThickness_adjust,N_("Thickness of the underbar."),0),
    MCDD(N_("底线额外下降:"),UnderbarExtraDescender,UnderbarExtraDescender_adjust,N_("Extra white space reserved below the underbar."),0),
    MCDD(N_("径向垂直间隙:"),RadicalVerticalGap,RadicalVerticalGap_adjust,N_("Space between the ink to of the\nexpression and the bar over it."),1),
    MCDD(N_("径向显示样式垂直间隙:"),RadicalDisplayStyleVerticalGap,RadicalDisplayStyleVerticalGap_adjust,N_("Space between the ink top of the\nexpression and the bar over it in display\nstyle."),0),
    MCDD(N_("径向规则厚度:"),RadicalRuleThickness,RadicalRuleThickness_adjust,N_("Thickness of the radical rule in\ndesigned or constructed radical\nsigns."),0),
    MCDD(N_("径向额外上升:"),RadicalExtraAscender,RadicalExtraAscender_adjust,N_("Extra white space reserved above the radical."),0),
    MCDD(N_("度前径向缩合:"),RadicalKernBeforeDegree,RadicalKernBeforeDegree_adjust,N_("Extra horizontal kern before the degree of a\nradical if such be present."),0),
    MCDD(N_("度后径向缩合:"),RadicalKernAfterDegree,RadicalKernAfterDegree_adjust,N_("Negative horizontal kern after the degree of a\nradical if such be present."),0),
    MCD(N_("根底升百分比:"),RadicalDegreeBottomRaisePercent,N_("Height of the bottom of the radical degree, if\nsuch be present, in proportion to the ascender\nof the radical sign."),0),
    MCD(N_("最小连接重叠:"),MinConnectorOverlap,N_("Minimum overlap of connecting glyphs during\nglyph construction."),1),
    MATH_CONSTANTS_DESCRIPTOR_EMPTY
};

struct MATH *MathTableNew(SplineFont *sf) {
    struct MATH *math = calloc(1,sizeof(struct MATH));	/* Too big for chunkalloc */
    int emsize = sf->ascent+sf->descent;
    DBounds b;
    SplineChar *sc;

    math->ScriptPercentScaleDown	= 80;
    math->ScriptScriptPercentScaleDown	= 60;
    math->DelimitedSubFormulaMinHeight	= emsize*1.5;
    /* No default given for math->DisplayOperatorMinHeight */
    /* No default given for math->MathLeading */
    /* The OpenType MATH specification does not suggest any value for
       math->AxisHeight. By default, we align the axis height with the middle
       of the + sign. */
    sc = SFGetChar(sf,'+',NULL);
    if ( sc!=NULL ) {
	SplineCharFindBounds(sc,&b);
	math->AxisHeight = (b.maxy+b.miny)/2;
    }
    sc = SFGetChar(sf,'x',NULL);
    if ( sc!=NULL ) {
	SplineCharFindBounds(sc,&b);
	math->AccentBaseHeight = b.maxy;
    }
    sc = SFGetChar(sf,'I',NULL);
    if ( sc!=NULL ) {
	SplineCharFindBounds(sc,&b);
	math->FlattenedAccentBaseHeight = b.maxy;
    }
    if ( sf->pfminfo.subsuper_set )
	math->SubscriptShiftDown = sf->pfminfo.os2_subyoff;
    math->SubscriptTopMax = math->AccentBaseHeight;		/* X-height */
    /* No default given for math->SubscriptBaselineDropMin */
    if ( sf->pfminfo.subsuper_set )
	math->SuperscriptShiftUp = sf->pfminfo.os2_supyoff;
    /* No default given for math->SuperscriptShiftUpCramped */
    math->SuperscriptBottomMin = math->AccentBaseHeight;	/* X-height */
    /* No default given for math->SuperscriptBaselineDropMax */
    math->SubSuperscriptGapMin = 4*sf->uwidth;			/* 4* default rule thickness */
    math->SuperscriptBottomMaxWithSubscript = math->AccentBaseHeight;	/* X-height */
    math->SpaceAfterScript = emsize/24;				/* .5pt at 12pt */
    /* No default given for math->UpperLimitGapMin */
    /* No default given for math->UpperLimitBaselineRiseMin */
    /* No default given for math->LowerLimitGapMin */
    /* No default given for math->LowerLimitBaselineDropMin */
    /* No default given for math->StackTopShiftUp */
    /* No default given for math->StackTopDisplayStyleShiftUp */
    /* No default given for math->StackBottomShiftDown */
    /* No default given for math->StackBottomDisplayStyleShiftDown */
    math->StackGapMin = 3*sf->uwidth;				/* 3* default rule thickness */
    math->StackDisplayStyleGapMin = 7*sf->uwidth;
    /* No default given for math->StretchStackTopShiftUp */
    /* No default given for math->StretchStackBottomShiftDown */
    math->StretchStackGapAboveMin = math->UpperLimitGapMin;
    math->StretchStackGapBelowMin = math->LowerLimitGapMin;
    /* No default given for math->FractionNumeratorShiftUp */
    math->FractionNumeratorDisplayStyleShiftUp = math->StackTopDisplayStyleShiftUp;
    /* No default given for math->FractionDenominatorShiftDown */
    math->FractionDenominatorDisplayStyleShiftDown = math->StackBottomDisplayStyleShiftDown;
    math->FractionNumeratorGapMin = sf->uwidth;
    math->FractionNumeratorDisplayStyleGapMin = 3*sf->uwidth;
    math->FractionRuleThickness = sf->uwidth;
    math->FractionDenominatorGapMin = sf->uwidth;
    math->FractionDenominatorDisplayStyleGapMin = 3*sf->uwidth;
    /* No default given for math->SkewedFractionHorizontalGap */
    /* No default given for math->SkewedFractionVerticalGap */
    math->OverbarVerticalGap = 3*sf->uwidth;
    math->OverbarRuleThickness = sf->uwidth;
    math->OverbarExtraAscender = sf->uwidth;
    math->UnderbarVerticalGap = 3*sf->uwidth;
    math->UnderbarRuleThickness = sf->uwidth;
    math->UnderbarExtraDescender = sf->uwidth;
    math->RadicalVerticalGap = sf->uwidth;
    math->RadicalDisplayStyleVerticalGap = sf->uwidth+.25*math->AccentBaseHeight; /* rule thickness + 1/4 X-height */
    math->RadicalRuleThickness = sf->uwidth;
    math->RadicalExtraAscender = sf->uwidth;
    math->RadicalKernBeforeDegree = 5*emsize/18;
    math->RadicalKernAfterDegree = -10*emsize/18;
    math->RadicalDegreeBottomRaisePercent = 60;

    math->MinConnectorOverlap = emsize/50;
return( math );
}

void MATHFree(struct MATH *math) {
    int i;

    if ( math==NULL )
return;

    for ( i=0; math_constants_descriptor[i].ui_name!=NULL; ++i ) {
	if ( math_constants_descriptor[i].devtab_offset>=0 )
	    DeviceTableFree( *(DeviceTable **) (((char *) math) + math_constants_descriptor[i].devtab_offset ) );
    }
    free(math);
}

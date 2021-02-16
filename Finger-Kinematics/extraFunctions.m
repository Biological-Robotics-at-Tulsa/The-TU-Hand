(* ::Package:: *)

BeginPackage["extraFunctions`"]

pointsTangent::usage="pointsTangent[p,c,r], Finds the two points at which a line passing through point p could possibly intersect a circle of radius r centered at point c."

Begin["`Private`"]

pointsTangent[p_,c_,r_]:=Module[{h,l,\[Phi]0,\[Phi],\[Theta]1,\[Theta]2,qx1,qy1,q1,qx2,qy2,q2},
	h=EuclideanDistance[p,c]; (*hypotenuse: distance from c to p*)
	(*a=r;*)
	If[h<r ,Return[{}]]; (*If point is inside circle, bail out*)

	l=Sqrt[h^2-r^2]; (*tendon length: distance from q to p*)
	\[Phi]0=ArcTan[p[[1]]-c[[1]],p[[2]]-c[[2]]];
	\[Phi]=ArcTan[l/r];

	(*Two Possible Solutions*)
	\[Theta]1=\[Phi]0+\[Phi];
	\[Theta]2=\[Phi]0-\[Phi];

	(*First Point of Tangency*)
	qx1=c[[1]]+r*Cos[\[Theta]1];
	qy1=c[[2]]+r*Sin[\[Theta]1];
	q1={qx1,qy1};

	(*Second Point of Tangency*)
	qx2=c[[1]]+r*Cos[\[Theta]2];
	qy2=c[[2]]+r*Sin[\[Theta]2];
	q2={qx2,qy2};

	Return[{q1,q2}]
];

End[]

EndPackage[]

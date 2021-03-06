/*
 * Rule.h
 *
 *  Created on: 20 Feb 2014
 *      Author: hieu
 */
#pragma once
#include <vector>
#include "Phrase.h"
#include "RulePhrase.h"
#include "moses/TypeDef.h"

class ConsistentPhrase;
class AlignedSentence;
class NonTerm;
class Parameter;


class Rule {
public:
	typedef std::set<std::pair<int,int> > Alignments;

	Rule(const Rule &copy); // do not implement

	// original rule with no non-term
	Rule(const NonTerm &lhsNonTerm, const AlignedSentence &alignedSentence);

	// extend a rule, adding 1 new non-term
	Rule(const Rule &copy, const NonTerm &nonTerm);

	virtual ~Rule();

	bool IsValid() const
	{ return m_isValid; }

	bool CanRecurse() const
	{ return m_canRecurse; }

	const NonTerm &GetLHS() const
	{ return m_lhs; }

	const ConsistentPhrase &GetConsistentPhrase() const;

	int GetNextSourcePosForNonTerm() const;

	void SetCount(float count)
	{ m_count = count; }
	float GetCount() const
	{ return m_count; }

	const Alignments &GetAlignments() const
	{ return m_alignments; }

	std::string Debug() const;
	void Output(std::ostream &out, bool forward, const Parameter &params) const;

	void Prevalidate(const Parameter &params);
	void CreateTarget(const Parameter &params);

	const RulePhrase &GetPhrase(Moses::FactorDirection direction) const
	{ return (direction == Moses::Input) ? m_source : m_target; }

protected:
	const NonTerm &m_lhs;
	const AlignedSentence &m_alignedSentence;
	RulePhrase m_source, m_target;
	float m_count;

	Alignments m_alignments;

	// in source order
	std::vector<const NonTerm*> m_nonterms;

	bool m_isValid, m_canRecurse;

	void CreateSource();
	void CreateAlignments();
	void CreateAlignments(int sourcePos, const std::set<const Word *> &targetWords);
	void CreateAlignments(int sourcePos, const RuleSymbol *targetSought);

	bool ContainTerm(const ConsistentPhrase &cp, const std::set<const Word*> &terms) const;
	int CalcScope() const; // not yet correctly calculated

	void NonTermContext(size_t ntInd, const ConsistentPhrase &cp, std::ostream &out) const;

};


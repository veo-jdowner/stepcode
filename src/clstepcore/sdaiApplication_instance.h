#ifndef STEPENTITY_H
#define        STEPENTITY_H 1

/*
* NIST STEP Core Class Library
* clstepcore/sdaiApplication_instance.h
* April 1997
* K. C. Morris
* David Sauder

* Development of this software was funded by the United States Government,
* and is not subject to copyright.
*/


///////////////////////////////////////////////////////////////////////////////
// SDAI_Application_instance used to be STEPentity

class SDAI_Application_instance : public SDAI_DAObject_SDAI
{
  private:
    int _cur;        // provides a built-in way of accessing attributes in order.

  public:
    STEPattributeList attributes;
    int               STEPfile_id;
    ErrorDescriptor   _error;
    std::string       p21Comment;
                                        // registry additions
    EntityDescriptor *eDesc;

    /**
    ** head entity for multiple inheritance.  If it is null then this
    ** SDAI_Application_instance is not part of a multiply inherited entity.  If it
    ** points to a SDAI_Application_instance then this SDAI_Application_instance is part of a mi entity
    ** and head points at the root SDAI_Application_instance of the primary inheritance
    ** path (the one that is the root of the leaf entity).
    */
    SDAI_Application_instance *headMiEntity;
    /// these form a chain of other entity parents for multiple inheritance
    SDAI_Application_instance *nextMiEntity;

  protected:
    int _complex;

 public:
    SDAI_Application_instance ();
    SDAI_Application_instance (int fileid, int complex = 0);
    virtual ~SDAI_Application_instance();

    int IsComplex() const { return _complex; }

    void StepFileId (int fid) { STEPfile_id = fid; }
    int StepFileId() const  { return STEPfile_id; }

    void AddP21Comment(const std::string &s, bool replace = true);
    void AddP21Comment(const char *s, bool replace = true);
    void DeleteP21Comment() { p21Comment = ""; }

    const std::string P21Comment() const { return p21Comment; }

    const char *EntityName( const char *schnm =NULL) const;

    virtual const EntityDescriptor * IsA(const EntityDescriptor *) const;
    
    virtual Severity ValidLevel(ErrorDescriptor *error, InstMgr *im, 
                        int clearError = 1);
    ErrorDescriptor &Error()        { return _error; }
                // clears entity's error and optionally all attr's errors
    void ClearError(int clearAttrs = 1);
                // clears all attr's errors
    void ClearAttrError();

    virtual SDAI_Application_instance *Replicate();

// ACCESS attributes in order.
    int AttributeCount();
    STEPattribute * NextAttribute();
    void ResetAttributes() { _cur =0; }
    
// READ
    virtual Severity STEPread(int id, int addFileId, 
                              class InstMgr * instance_set,
                              istream& in =cin, const char * currSch = NULL,
                              bool useTechCor = true );
    virtual void STEPread_error(char c, int index, istream& in);

// WRITE
    virtual void STEPwrite(ostream& out =cout, const char *currSch =NULL,
                           int writeComments = 1);
    virtual const char * STEPwrite(std::string &buf, const char *currSch =NULL);

    void WriteValuePairs(ostream& out, const char *currSch =NULL, 
                         int writeComments = 1, int mixedCase = 1);

    void         STEPwrite_reference (ostream& out =cout);
    const char * STEPwrite_reference (std::string &buf);

    void beginSTEPwrite(ostream& out =cout); ///< writes out the SCOPE section
    void endSTEPwrite(ostream& out =cout);

// MULTIPLE INHERITANCE
    int MultipleInheritance() { return !(headMiEntity == 0); }

    void HeadEntity(SDAI_Application_instance *se) { headMiEntity = se; }
    SDAI_Application_instance * HeadEntity() { return headMiEntity; }

    SDAI_Application_instance *GetNextMiEntity() { return nextMiEntity; }
    SDAI_Application_instance *GetMiEntity(char *EntityName);
    void AppendMultInstance(SDAI_Application_instance *se);

 protected:
    STEPattribute * GetSTEPattribute (const char *);
    STEPattribute * MakeDerived (const char *);
    STEPattribute * MakeRedefined (STEPattribute *redefiningAttr, 
                                   const char * nm);

    virtual void CopyAs (SDAI_Application_instance *);
    void PrependEntityErrMsg();
};

// current style of CORBA handles for Part 23 - NOTE - used for more than CORBA
typedef SDAI_Application_instance* SDAI_Application_instance_ptr;
typedef SDAI_Application_instance_ptr SDAI_Application_instance_var;

#endif
